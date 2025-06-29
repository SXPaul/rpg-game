/**
 * @file	Polygon.h
 * @brief   �����ģ�嶨��
 * @author	Arty
 **/


#pragma once
#include"Box2D.h" 
#include"Circle.h" 
#include"Segment2D.h"
#include<vector>



namespace Math
{
	/* ����� */
	template<typename T>
	struct TPolygon
	{
		std::vector<TVector2<T>>initVertices;

		std::vector<TVector2<T>>vertices;

		TVector2<T>mean;

		bool bIsConvex;

		bool bIsValid;

		TPolygon<T>()
		{
			initVertices = {};
			vertices = {};
			bIsConvex = true;
			bIsValid = false;
		}

		/**
		 * @brief ������вι���(ʹ��Ĭ�ϵ���������)
		 * @param[in] vts ָ������ζ����������(���밴��˳ʱ�������ʱ������)
		 **/
		TPolygon<T>(const std::vector<TVector2<T>>& vts)
		{
			initVertices = SimplifyVertices(vts);
			vertices.resize(initVertices.size(), TVector2<T>::ZeroVector);
			bIsConvex = IsConvex(initVertices);
			bIsValid = (vts.size() >= 3);
		}

		/**
	     * @brief ������вι���(�ֶ�ǿ��ָ������)
	     * @param[in] vts ָ������ζ����������(���밴��˳ʱ�������ʱ������)
	     * @param[in] mean ָ�����������
	     **/
		TPolygon<T>(const std::vector<TVector2<T>>& vts, const TVector2<T>& mean)
		{
			initVertices = SimplifyVertices(vts);
			vertices.resize(initVertices.size(), TVector2<T>::ZeroVector);
			bIsConvex = IsConvex(initVertices);
			bIsValid = (vts.size() >= 3);
		}

		//��������ת��
		void UpdateTransform(const TVector2<T>& newMean, T newDegree = T(0), const TVector2<T>& newScale = TVector2<T>::UnitVector)
		{
			mean = newMean;

			if (newScale == TVector2<T>::UnitVector && newDegree == T(0))
			{
				for (int i = 0; i < initVertices.size(); i++)
				{
					vertices[i] = mean + initVertices[i];
				}
				return;
			}
			if (newScale != TVector2<T>::UnitVector)
			{
				for (int i = 0; i < initVertices.size(); i++)
				{
					vertices[i] = initVertices[i] * newScale;
				}
			}
			if (newDegree != T(0))
			{
				for (int i = 0; i < initVertices.size(); i++)
				{
					vertices[i] = TVector2<T>::RotateAround(newDegree, TVector2<T>::ZeroVector, vertices[i]);
				}
			}
			for (int i = 0; i < initVertices.size(); i++)
			{
				vertices[i] += mean;
			}
		}

		//��ȡ�߽緶Χ
		TBox2<T> GetExtents() const
		{
			T maxX, maxY, minX, minY;
			maxX = minX = vertices[0].x;
			maxY = minY = vertices[0].y;
			for (auto& vertex : vertices)
			{
				maxX = vertex.x > maxX ? vertex.x : maxX;
				maxY = vertex.x > maxY ? vertex.x : maxY;
				minX = vertex.x < minX ? vertex.x : minX;
				minY = vertex.x < minY ? vertex.x : minY;
			}
			return TBox2<T>(TVector2<T>(minX, minY), TVector2<T>(maxX, maxY));
		}

		//�ж�һ�����Ƿ�λ�ڶ����֮��
		bool IsInside(const TVector2<T>& testPoint) const
		{
			if (!bIsValid)
			{
				return false;
			}

			//�Ӹõ㴹ֱ������һ�����ߣ���������߽�����Ϊ�������ڶ������
			int n = vertices.size();
			int num = 0;
			for (int i = 0, j = n - 1; i < n; j = i++)
			{
				if (FMath::IsSmallNumber(vertices[i].x - vertices[j].x))
				{
					continue;//���ñߴ�ֱ��ֱ������
				}
				T y = (vertices[i].y - vertices[j].y) / (vertices[i].x - vertices[j].x) * (testPoint.x - vertices[i].x) + vertices[i].y;
				if (FMath::Min(vertices[i].y, vertices[j].y) < y && y <= FMath::Max(vertices[i].y, vertices[j].y) && y > testPoint.y)
				{
					num++;
				}
			}
			return num % 2 == 1;
		}

		//��������һ��������ཻ�����洢�����Ϣ
		FORCEINLINE bool Intersects(const TPolygon<T>& other, float& depth, TVector2<T>& normal, TVector2<T>& point) const;

		//��������һ��Բ���ཻ�����洢�����Ϣ
		FORCEINLINE bool Intersects(const TCircle<T>& other, float& depth, TVector2<T>& normal, TVector2<T>& point) const;

		//�ж϶�����Ƿ�Ϊ͹�����
		static FORCEINLINE bool IsConvex(const std::vector<TVector2<T>>& vts);

		//�򻯶���ζ��㼯��(ȥ��λ�ڱ��ϵĶ��ඥ�㣬��������������ԭ�����)
		static FORCEINLINE std::vector<TVector2<T>> SimplifyVertices(const std::vector<TVector2<T>>& vts);

		/**
		 * @brief ��ȡ�������������
		 * @param[in] vts ����ζ��㼯��
		 **/
		static FORCEINLINE TVector2<T> FindArithmeticMean(const std::vector<TVector2<T>>& vts);
	};

	template<typename T>
	FORCEINLINE bool TPolygon<T>::Intersects(const TPolygon<T>& other, float& depth, TVector2<T>& normal, TVector2<T>& point) const
	{
		if (bIsConvex && other.bIsConvex)//SAT
		{
			size_t n = vertices.size();
			for (int i = 0, j = n - 1; i < n; j = i++)
			{
				TVector2<T> edge = vertices[i] - vertices[j];
				TVector2<T> axis(-edge.y, edge.x);
				axis.Normalize();

				T minA = TVector2<T>::DotProduct(vertices[0], axis);
				T maxA = minA;
				for (int i = 1; i < n; i++)
				{
					T proj = TVector2<T>::DotProduct(vertices[i], axis);

					if (proj < minA) minA = proj;
					if (proj > maxA) maxA = proj;
				}

				T minB = TVector2<T>::DotProduct(other.vertices[0], axis);
				T maxB = minB;
				for (int i = 1; i < n; i++)
				{
					T proj = TVector2<T>::DotProduct(other.vertices[i], axis);

					if (proj < minB) minB = proj;
					if (proj > maxB) maxB = proj;
				}

				if (minA >= maxB || minB >= maxA)
				{
					return false;
				}

				float axisDepth = FMath::Min(maxB - minA, maxA - minB);
				if (axisDepth < depth)
				{
					depth = axisDepth;
					normal = TVector2<T>::DotProduct(normal, other.mean - mean) > 0 ? axis : -axis;
				}
			}

			n = other.vertices.size();
			for (int i = 0, j = n - 1; i < n; j = i++)
			{
				TVector2<T> edge = other.vertices[i] - other.vertices[j];
				TVector2<T> axis(-edge.y, edge.x);
				axis.Normalize();

				T minA = TVector2<T>::DotProduct(vertices[0], axis);
				T maxA = minA;
				for (int i = 1; i < n; i++)
				{
					T proj = TVector2<T>::DotProduct(vertices[i], axis);

					if (proj < minA) minA = proj;
					if (proj > maxA) maxA = proj;
				}

				T minB = TVector2<T>::DotProduct(other.vertices[0], axis);
				T maxB = minB;
				for (int i = 1; i < n; i++)
				{
					T proj = TVector2<T>::DotProduct(other.vertices[i], axis);

					if (proj < minB) minB = proj;
					if (proj > maxB) maxB = proj;
				}

				if (minA >= maxB || minB >= maxA)
				{
					return false;
				}

				float axisDepth = FMath::Min(maxB - minA, maxA - minB);
				if (axisDepth < depth)
				{
					depth = axisDepth;
					normal = TVector2<T>::DotProduct(normal, other.mean - mean) > 0 ? axis : -axis;
				}
			}

			return true;
		}
		else//�Ƿ����һ�����㴦����һ�������
		{
			int n = vertices.size();
			for (auto& p : other.vertices)
			{
				if (IsInside(p))
				{
					point = p;

					TSegment2<T> aimSegment;
					T aimDist = T(0);
					for (int i = 0, j = n - 1; i < n; j = i++)
					{
						TSegment2<T> segment = TSegment2<T>(vertices[i], vertices[j]);
						if (segment.Dist(point) < aimDist)
						{
							aimSegment = segment;
						}
					}
					depth = aimSegment.Dist(point);
					normal = TVector2<T>(point - aimSegment.ClosestPoint(point));
					return true;
				}
			}
			for (int i = 0, j = n - 1; i < n; j = i++)
			{
				TSegment2<T> segment1(vertices[i], vertices[j]);
				int m = other.vertices.size();
				for (int a = 0, b = m - 1; a < m; b = a++)
				{
					TSegment2<T> segment2(vertices[a], vertices[b]);
					if (segment1.Intersects(segment2, point))
					{
						return true;
					}
				}
			}
			return false;
		}
	}

	template<typename T>
	FORCEINLINE bool TPolygon<T>::Intersects(const TCircle<T>& other, float& depth, TVector2<T>& normal, TVector2<T>& point) const
	{
		size_t n = vertices.size();
		for (int i = 0, j = n - 1; i < n; j = i++)
		{
			TVector2<T> edge = vertices[i] - vertices[j];
			TVector2<T> axis(-edge.y, edge.x);
			axis.Normalize();

			T minA = TVector2<T>::DotProduct(vertices[0], axis);
			T maxA = minA;
			for (int i = 1; i < n; i++)
			{
				T proj = TVector2<T>::DotProduct(vertices[i], axis);

				if (proj < minA) minA = proj;
				if (proj > maxA) maxA = proj;
			}

			T minB = TVector2<T>::DotProduct(other.center, axis) - other.radius;
			T maxB = minB + other.radius * 2;

			if (minA >= maxB || minB >= maxA)
			{
				return false;
			}

			float axisDepth = FMath::Min(maxB - minA, maxA - minB);
			if (axisDepth < depth)
			{
				depth = axisDepth;
				normal = TVector2<T>::DotProduct(normal, other.center - mean) > 0 ? axis : -axis;
			}
		}
		return false;
	}

	template<typename T>
	FORCEINLINE bool TPolygon<T>::IsConvex(const std::vector<TVector2<T>>& vts)
	{ 
		if (vts.size() < 3)return false;

		bool isPositive = TVector2<T>::CrossProduct(vts.back() - vts[0], vts[0] - vts[1]) > 0;
		for (size_t i = 1; i < vts.size() - 1; ++i)
		{
			if ((TVector2<T>::CrossProduct(vts[i - 1] - vts[i], vts[i] - vts[i + 1]) > 0) ^ isPositive)
			{
				return false;
			}
		}
		if ((TVector2<T>::CrossProduct(vts[vts.size() - 2] - vts.back(), vts.back() - vts[0]) > 0) ^ isPositive)
		{
			return false;
		}

		return true;
	}

	template<typename T>
	FORCEINLINE std::vector<TVector2<T>> TPolygon<T>::SimplifyVertices(const std::vector<TVector2<T>>& vts)
	{
		std::vector<TVector2<T>> simplifiedVertices;

		if (vts.size() < 3) return simplifiedVertices;

		if (!FMath::IsSmallNumber(TVector2<T>::CrossProduct(vts.back() - vts[0], vts[0] - vts[1])))
		{
			simplifiedVertices.push_back(vts[0]);
		}
		for (size_t i = 1; i < vts.size() - 1; ++i)
		{
			if (!FMath::IsSmallNumber(TVector2<T>::CrossProduct(vts[i - 1] - vts[i], vts[i] - vts[i + 1])))
			{
				simplifiedVertices.push_back(vts[i]);
			}
		}
		if (!FMath::IsSmallNumber(TVector2<T>::CrossProduct(vts[vts.size() - 2] - vts.back(), vts.back() - vts[0])))
		{
			simplifiedVertices.push_back(vts.back());
		}

		TVector2<T>offset = FindArithmeticMean(simplifiedVertices);
		for (auto& point : simplifiedVertices)
		{
			point -= offset;
		}

		return simplifiedVertices;
	}

	template<typename T>
	FORCEINLINE TVector2<T> TPolygon<T>::FindArithmeticMean(const std::vector<TVector2<T>>& vts)
	{
		TVector2<T> sum = TVector2<T>::ZeroVector;
		for (auto& v : vts)
		{
			sum += v;
		}
		return sum / T(vts.size());
	}
}
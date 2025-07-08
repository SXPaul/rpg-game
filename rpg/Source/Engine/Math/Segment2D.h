/**
 * @file	Segment2D.h
 * @brief   ��ά�߶�ģ�嶨��
 * @author	Arty
 **/


#pragma once
#include"Ray2D.h" 


namespace Math
{
	template<typename T>
	struct TSegment2
	{
		TRay2<T> ray1;
		TRay2<T> ray2;

		TSegment2()
		{
			ray1 = TRay2<T>();
			ray2 = TRay2<T>();
		}

		TSegment2(const TVector2<T>& p1, const TVector2<T>& p2)
		{
			ray1 = TRay2<T>(p1, p2 - p1);
			ray2 = TRay2<T>(p2, p1 - p2);
		}

		bool operator==(const TSegment2<T>& other) const
		{
			return ((ray1.origin == other.ray1.origin) && (ray2.origin == other.ray2.origin))
				|| ((ray1.origin == other.ray2.origin) && (ray2.origin == other.ray1.origin));
		}

		bool operator!=(const TSegment2<T>& other) const
		{
			return !(*this == other);
		}

		//�ж�ĳ���Ƿ�λ���߶���
		bool IsOn(const TVector2<T>& point) const
		{
			return ray1.IsOn(point) && ray2.IsOn(point);
		}

		/**
		 * @brief �ҵ��㵽�߶ε���С�����ƽ��
		 * @param[in] ��Ҫ��ѯ�ĵ�
		 * @return �㵽�߶���С�����ƽ��
		 */
		T DistSquared(const TVector2<T>& point) const
		{
			if (ray1.GetParameter(point) >= 0 && ray2.GetParameter(point) >= 0)
			{
				return ray1.DistSquared(point);
			}
			return FMath::Min(TVector2<T>::DistSquared(point, ray1.origin), TVector2<T>::DistSquared(point, ray2.origin));
		}

		/**
		 * @brief �ҵ��㵽�߶ε���С����
		 * @param[in] ��Ҫ��ѯ�ĵ�
		 * @return �㵽�߶���С����
		 */
		T Dist(const TVector2<T>& point) const
		{
			return FMath::Sqrt(DistSquared(point));
		}

		/**
		 * @brief �ҵ��߶��Ͼ���ĳ������ĵ�
		 * @param[in] ��Ҫ��ѯ�ĵ�
		 * @return ����ĳ������ĵ�
		 */
		TVector2<T> ClosestPoint(const TVector2<T>& point) const
		{
			if (ray1.GetParameter(point) >= 0 && ray2.GetParameter(point) >= 0)
			{
				return ray1.PointAt(ray1.GetParameter(point));
			}
			else if (ray1.GetParameter(point) < 0)
			{
				return ray1.origin;
			}
			else
			{
				return ray2.origin;
			}
		}

		//�ж��Ƿ�����һ���߶��ཻ
		bool Intersects(const TSegment2<T>& segment, TVector2<T>& point) const
		{
			T x1 = ray1.origin.x, y1 = ray1.origin.y;
			T x2 = ray2.origin.x, y2 = ray2.origin.y;
			T x3 = segment.ray1.origin.x, y3 = segment.ray1.origin.y;
			T x4 = segment.ray2.origin.x, y4 = segment.ray2.origin.y;

			double det = (x2 - x1) * (y4 - y3) - (y2 - y1) * (x4 - x3);
			if (FMath::Abs(det) < AE_SMALL_NUMBER) return false; 

			double t = ((x3 - x1) * (y4 - y3) - (y3 - y1) * (x4 - x3)) / det;
			double s = ((x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1)) / det;

			if (t < 0 || t > 1 || s < 0 || s > 1) return false; 

			point.x = x1 + t * (x2 - x1);
			point.y = y1 + t * (y2 - y1);
			return true;
		}
	};
}
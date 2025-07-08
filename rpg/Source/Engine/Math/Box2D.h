/**
 * @file	Box2D.h
 * @brief   ��ά���ο�ģ�嶨��
 * @author	Arty
 **/


#pragma once
#include"Vector2D.h"


namespace Math
{
	/* ��ά���ο� */
	template<typename T>
	struct TBox2
	{
		TVector2<T> min;

		TVector2<T> max;

		TBox2<T>()
			: min(0, 0), max(0, 0) {}

		TBox2<T>(const TVector2<T>& inMin, const TVector2<T>& inMax)
			: min(inMin), max(inMax)
		{
			if (inMin.x >= inMax.x || inMin.y >= inMax.y)
			{
				min = max = TVector2<T>::ZeroVector;
			}
		}

		FORCEINLINE TBox2<T>(const TVector2<T>& center, T width, T height);

		static const TBox2<T> EmptyBox;

		bool operator==(const TBox2<T>& another) const
		{
			return min == another.min && max == another.max;
		}

		bool operator!=(const TBox2<T>& another) const
		{
			return min != another.min || max != another.max;
		}

		//��ȡ�������ĵ�
		TVector2<T> GetCenter() const
		{
			return TVector2<T>((min + max) * 0.5f);
		}

		//��ȡ���δ�С
		TVector2<T> GetSize() const
		{
			return TVector2<T>(max - min);
		}

		//��ȡ���δ�С��һ��
		TVector2<T> GetHalf() const
		{
			return 0.5f * TVector2<T>(max - min);
		}

		//��ȡ�������
		T GetArea() const
		{
			return (max.x - min.x) * (max.y - min.y);
		}

		//�ж�һ�����Ƿ�λ�ھ���֮��
		bool IsInside(const TVector2<T>& testPoint) const
		{
			return ((testPoint.x > min.x) && (testPoint.x < max.x) && (testPoint.y > min.y) && (testPoint.y < max.y));
		}

		//�ж�һ�����Ƿ�λ�ھ���֮��(������Ե)
		bool IsInsideOrOn(const TVector2<T>& testPoint) const
		{
			return ((testPoint.x >= min.x) && (testPoint.x <= max.x) && (testPoint.y >= min.y) && (testPoint.y <= max.y));
		}

		//�ж�һ�����Ƿ�λ�ھ��α�Ե��
		bool IsOn(const TVector2<T>& testPoint) const
		{
			return !IsInside(testPoint) && IsInsideOrOn(testPoint);
		}

		//������������Ƿ��ཻ
		FORCEINLINE bool Intersects(const TBox2<T>& other) const;

		//��ȡ�ص����־���
		FORCEINLINE TBox2<T> Overlaps(const TBox2<T>& other) const;

		//�õ����ξ���Ŀ���������Ǹ���
		FORCEINLINE TVector2<T> GetClosestPointTo(const TVector2<T>& point) const;
	};

	template<typename T>
	FORCEINLINE TBox2<T>::TBox2(const TVector2<T>& center, T width, T height)
	{
		min = center - TVector2<T>(width * 0.5f, height * 0.5f);
		max = center + TVector2<T>(width * 0.5f, height * 0.5f);
	}

	template<typename T>
	FORCEINLINE bool TBox2<T>::Intersects(const TBox2<T>& other) const
	{
		if ((min.x > other.max.x) || (other.min.x > max.x))
		{
			return false;
		}
		if ((min.y > other.max.y) || (other.min.y > max.y))
		{
			return false;
		}
		return true;
	}

	template<typename T>
	FORCEINLINE TBox2<T> TBox2<T>::Overlaps(const TBox2<T>& other) const
	{
		if (!Intersects(other))
		{
			return EmptyBox;
		}

		TVector2<T> minVector, maxVector;

		minVector.x = FMath::Max(min.x, other.min.x);
		maxVector.x = FMath::Min(max.x, other.max.x);

		minVector.y = FMath::Max(min.y, other.min.y);
		maxVector.y = FMath::Min(max.y, other.max.y);

		return TBox2<T>(minVector, maxVector);
	}

	template<typename T>
	FORCEINLINE TVector2<T> TBox2<T>::GetClosestPointTo(const TVector2<T>& point) const
	{
		TVector2<T> closestPoint = point;

		if (point.x < min.x)
		{
			closestPoint.x = min.x;
		}
		else if (point.x > max.x)
		{
			closestPoint.x = max.x;
		}

		if (point.y < min.y)
		{
			closestPoint.y = min.y;
		}
		else if (point.y > max.y)
		{
			closestPoint.y = max.y;
		}

		return closestPoint;
	}

	template<typename T>
	const TBox2<T> TBox2<T>::EmptyBox = TBox2<T>();
}
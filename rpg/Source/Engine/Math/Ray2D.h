/**
 * @file	Ray2D.h
 * @brief   ��ά����ģ�嶨��
 * @author	Arty
 **/


#pragma once
#include"Vector2D.h" 


namespace Math
{
	template<typename T>
	struct TRay2
	{
		TVector2<T> origin;

		TVector2<T> direction;

		TRay2()
		{
			origin = TVector2<T>::ZeroVector;
			direction = TVector2<T>::UnitVector;
		}

		TRay2(const TVector2<T>& origin, const TVector2<T>& direction)
		{
			this->origin = origin;
			this->direction = direction;
			this->direction.Normalize();
		}

		bool operator==(const TRay2<T>& other) const
		{
			return (origin == other.origin) && direction.Equals(other.direction);
		}

		bool operator!=(const TRay2<T>& other) const
		{
			return !(*this == other);
		}

		/**
		 * @brief ��ȡ������ĳһ��
		 * @param[in] rayParameter �����߷���ı�������
		 * @return �����ϵĵ�
		 */
		TVector2<T> PointAt(T rayParameter) const
		{
			return origin + rayParameter * direction;
		}

		/**
		 * @brief ��ȡĿ�����������ͶӰ��������ı�������(�����߷���Ϊ��)
		 * @param[in] ��Ҫ��ѯ�ĵ�
		 * @return Ŀ�����������ͶӰ��������ı�������
		 */
		T GetParameter(const TVector2<T>& point) const
		{
			return TVector2<T>::DotProduct((point - origin), direction);
		}

		//�ж�ĳ���Ƿ�λ��������
		bool IsOn(const TVector2<T>& point) const
		{
			if (point == origin)
			{
				return true;
			}
			return FMath::IsSmallNumber(DistSquared(point));
		}

		/**
		 * @brief �ҵ��㵽���ߵ���С�����ƽ��
		 * @param[in] ��Ҫ��ѯ�ĵ�
		 * @return �㵽������С�����ƽ��
		 */
		T DistSquared(const TVector2<T>& point) const
		{
			T rayParameter = GetParameter(point);
			if (rayParameter < 0)
			{
				return TVector2<T>::DistSquared(origin, point);
			}
			else
			{
				return TVector2<T>::DistSquared(PointAt(rayParameter), point);
			}
		}

		/**
		 * @brief �ҵ��㵽���ߵ���С����
		 * @param[in] ��Ҫ��ѯ�ĵ�
		 * @return �㵽������С����
		 */
		T Dist(const TVector2<T>& point) const
		{
			return FMath::Sqrt(DistSquared(point));
		}

		/**
		 * @brief �ҵ������Ͼ���ĳ������ĵ�
		 * @param[in] ��Ҫ��ѯ�ĵ�
		 * @return ����ĳ������ĵ�
		 */
		TVector2<T> ClosestPoint(const TVector2<T>& point) const
		{
			T rayParameter = GetParameter(point);
			if (rayParameter < 0)
			{
				return origin;
			}
			else
			{
				return PointAt(rayParameter);
			}
		}
	};

}	
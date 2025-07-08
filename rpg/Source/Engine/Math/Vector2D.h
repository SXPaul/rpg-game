/**
 * @file	Vector2D.h
 * @brief   ��ά����ģ�嶨��
 * @author	Arty
 **/


#pragma once
#include<iostream>
#include<string>
#include"Core/Math.h"


namespace Math
{
	/* ��ά���� */
	template<typename T>
	struct TVector2
	{
		static_assert(std::disjunction_v<std::is_integral<T>, std::is_floating_point<T>>,
			"T must be either an integral type or a floating point type");

		T x, y;
		FORCEINLINE TVector2();
		FORCEINLINE TVector2(T a, T b);
		explicit FORCEINLINE TVector2(T v);

		static const TVector2<T> ZeroVector;
		static const TVector2<T> UnitVector;

		FORCEINLINE TVector2<T> Zero() const { return ZeroVector; }
		FORCEINLINE TVector2<T> One() const { return UnitVector; }

		//��ȡƽ����
		FORCEINLINE T SizeSquared() const;

		//��ȡ��������
		FORCEINLINE T Size() const;

		//��ȡ����ֵ
		FORCEINLINE TVector2<T> GetAbs() const;

		//����ֵ��
		FORCEINLINE void MakeAbs();

		//���㻯, ������ֵ��С��ֵ������
		FORCEINLINE void MakeZero(T tolerance = AE_KINDA_SMALL_NUMBER);

		/**
		 * @brief ��ȡ��λ����
		 * @param[in] tolerance ���ڴ���һ�������������ܽ�����ƽ���͵���С��ֵ
		 **/
		FORCEINLINE TVector2<T> GetSafeNormal(T tolerance = AE_SMALL_NUMBER) const;

		/**
		 * @brief ��һ������
		 * @param[in] tolerance ���ڴ���һ�������������ܽ�����ƽ���͵���С��ֵ
		 * @return �Ƿ��һ���ɹ�
		 **/
		FORCEINLINE bool Normalize(T tolerance = AE_SMALL_NUMBER);

		/**
		 * @brief �����������з���������ĳ����Χ��
		 **/
		FORCEINLINE TVector2<T> ClampAxes(T minAxisVal, T maxAxisVal) const;

		/**
	     * @brief ���һ�������Ƿ�ɽ���Ϊ������
	     * @param[in] tolerance �ɽ���Ϊ�����ֵ
	     * @return �Ƿ�ƽ�������
	     */
		FORCEINLINE bool IsNearlyZero(T tolerance = AE_KINDA_SMALL_NUMBER) const;

		/**
	     * @brief ���һ�������Ƿ�����һ�������������
	     * @param[in] tolerance �ɽ��ƿ�����ȵ������ֵ
	     * @return �Ƿ�������
	     */
		FORCEINLINE bool Equals(const TVector2<T>& v, T tolerance = AE_KINDA_SMALL_NUMBER) const;

		//������ת��Ϊ�ַ���
		FORCEINLINE std::string ToString() const;


		TVector2<T> operator+(const TVector2<T>& another) const
		{
			return TVector2<T>(x + another.x, y + another.y);
		}

		TVector2<T> operator-(const TVector2<T>& another) const
		{
			return TVector2<T>(x - another.x, y - another.y);
		}

		TVector2<T>& operator+=(const TVector2<T>& another)
		{
			x += another.x; y += another.y;
			return *this;
		}

		TVector2<T>& operator-=(const TVector2<T>& another)
		{
			x -= another.x; y -= another.y;
			return *this;
		}

		TVector2<T> operator-() const
		{
			return TVector2<T>(-x, -y);
		}

	    bool operator==(const TVector2<T>& another) const
		{
			return x == another.x && y == another.y;
		}

		bool operator!=(const TVector2<T>& another) const
		{
			return x != another.x || y != another.y;
		}

		bool operator>(const TVector2<T>& another) const
		{
			return x > another.x && y > another.y;
		}

		bool operator<(const TVector2<T>& another) const
		{
			return x < another.x && y < another.y;
		}

		bool operator>=(const TVector2<T>& another) const
		{
			return x >= another.x && y >= another.y;
		}

		bool operator<=(const TVector2<T>& another) const
		{
			return x <= another.x && y <= another.y;
		}

		TVector2<T> operator*(float scale) const
		{
			return TVector2<T>(x * scale, y * scale);
		}

		TVector2<T>& operator*=(float scale)
		{
			x *= scale; y *= scale;
			return *this;
		}

		TVector2<T> operator/(float scale) const
		{
			return TVector2<T>(x / scale, y / scale);
		}

		TVector2<T>& operator/=(float scale)
		{
			x /= scale; y /= scale;
			return *this;
		}

		TVector2<T> operator*(const TVector2<T>& another) const
		{
			return TVector2<T>(x * another.x, y * another.y);
		}

		TVector2<T> operator/(const TVector2<T>& another) const
		{
			return TVector2<T>(x / another.x, y / another.y);
		}

		T operator[](int32 index) const
		{
			index = FMath::Clamp(index, 0, 1);
			return (index == 0) ? x : y;
		}

		//���
		T operator|(const TVector2<T>& v) const
		{
			return x * v.x + y * v.y;
		}

		//���
		T operator^(const TVector2<T>& v) const
		{
			return x * v.y - v.x * y;
		}

		//�������
		static FORCEINLINE T DotProduct(const TVector2<T>& v1, const TVector2<T>& v2);

		//�����������z��ֵΪ�����
		static FORCEINLINE T CrossProduct(const TVector2<T>& v1, const TVector2<T>& v2);

		//��ȡ������������ƽ��
		static FORCEINLINE T DistSquared(const TVector2<T>& v1, const TVector2<T>& v2);

		//��ȡ��������֮��ľ���
		static FORCEINLINE T Distance(const TVector2<T>& v1, const TVector2<T>& v2);

		//������ת��Ϊ�Ƕ�
		static FORCEINLINE float VectorToDegree(const TVector2<T>& v);

		//���Ƕ�ת��Ϊ��λ����
		static FORCEINLINE TVector2<T> DegreeToVector(float angle);

		/**
		 * @brief ����ĳһ������ת��Ľ��������
		 * @param[in] angle        ����ת�Ƕ�
		 * @param[in] v            ����ת����
		 * @return ��ת�������
		 */
		static FORCEINLINE TVector2<T> RotateVector(float angle, const TVector2<T>& v);

		/**
		 * @brief ����ĳһ������һ��Ϊ������ת��Ľ��������
		 * @param[in] angle        ����ת�Ƕ�
		 * @param[in] center       ��ת����
		 * @param[in] p            ����ת��
		 * @return ��ת��ĵ������
		 */
		static FORCEINLINE TVector2<T> RotateAround(float angle, const TVector2<T>& center, const TVector2<T>& p);

		//������ u ͶӰ������ v ���ڵ�ֱ����
		static FORCEINLINE TVector2<T> ProjectVector(const TVector2<T>& u, const TVector2<T>& v);
	};

	template<typename T>
	FORCEINLINE std::ostream& operator<<(std::ostream& out, const TVector2<T>& vec)
	{
		return out << "(" << vec.x << "," << vec.y << ")";
	}

	template<typename T>
	FORCEINLINE TVector2<T> operator*(float scale, TVector2<T> vec)
	{
		return TVector2<T>(vec.x * scale, vec.y * scale);
	}

	template<typename T>
	FORCEINLINE TVector2<T>::TVector2()
		:x(0), y(0) {}

	template<typename T>
	FORCEINLINE TVector2<T>::TVector2(T a, T b)
		: x(a), y(b) {}

	template<typename T>
	FORCEINLINE TVector2<T>::TVector2(T v)
		: x(v), y(v) {}

	template<typename T>
	FORCEINLINE T TVector2<T>::SizeSquared() const
	{
		return x * x + y * y;
	}

	template<typename T>
	FORCEINLINE T TVector2<T>::Size() const
	{
		return FMath::Sqrt(x * x + y * y);
	}

	template<typename T>
	FORCEINLINE TVector2<T> TVector2<T>::GetAbs() const
	{
		return TVector2<T>(FMath::Abs(x), FMath::Abs(y));
	}

	template<typename T>
	FORCEINLINE void TVector2<T>::MakeAbs()
	{
		x = FMath::Abs(x);
		y = FMath::Abs(y);
	}

	template<typename T>
	FORCEINLINE void TVector2<T>::MakeZero(T tolerance)
	{
		x = FMath::Abs(x) < tolerance ? T(0) : x;
		y = FMath::Abs(y) < tolerance ? T(0) : y;
	}

	template<typename T>
	FORCEINLINE TVector2<T> TVector2<T>::GetSafeNormal(T tolerance) const
	{
		const T squareSum = x * x + y * y;
		if (squareSum > tolerance)
		{
			const T scale = FMath::InvSqrt(squareSum);
			return TVector2<T>(x, y) * scale;
		}
		return ZeroVector;
	}

	template<typename T>
	FORCEINLINE bool TVector2<T>::Normalize(T tolerance)
	{
		const T squareSum = x * x + y * y;
		if (squareSum > tolerance)
		{
			const T scale = FMath::InvSqrt(squareSum);
			x *= scale, y *= scale;
			return true;
		}
		x = y = T(0);
		return false;
	}

	template<typename T>
	FORCEINLINE TVector2<T> TVector2<T>::ClampAxes(T minAxisVal, T maxAxisVal) const
	{
		return TVector2<T>(FMath::Clamp(x, minAxisVal, maxAxisVal), FMath::Clamp(y, minAxisVal, maxAxisVal));
	}

	template<typename T>
	FORCEINLINE bool TVector2<T>::IsNearlyZero(T tolerance) const
	{
		return FMath::Abs(x) <= tolerance && FMath::Abs(y) <= tolerance;
	}

	template<typename T>
	FORCEINLINE bool TVector2<T>::Equals(const TVector2<T>& v, T tolerance) const
	{
		return FMath::Abs(x - v.x) <= tolerance && FMath::Abs(y - v.y) <= tolerance;
	}

	template<typename T>
	FORCEINLINE std::string TVector2<T>::ToString() const
	{
		return "(" + std::to_string((int)x) + "," + std::to_string((int)y) + ")";
	}

	template<typename T>
	FORCEINLINE T TVector2<T>::DotProduct(const TVector2<T>& v1, const TVector2<T>& v2)
	{
		return v1 | v2;
	}

	template<typename T>
	FORCEINLINE T TVector2<T>::CrossProduct(const TVector2<T>& v1, const TVector2<T>& v2)
	{
		return v1 ^ v2;
	}

	template<typename T>
	FORCEINLINE T TVector2<T>::DistSquared(const TVector2<T>& v1, const TVector2<T>& v2)
	{
		return TVector2<T>(v1 - v2).SizeSquared();
	}

	template<typename T>
	FORCEINLINE T TVector2<T>::Distance(const TVector2<T>& v1, const TVector2<T>& v2)
	{
		return FMath::Sqrt(DistSquared(v1, v2));
	}

	template<typename T>
	FORCEINLINE float TVector2<T>::VectorToDegree(const TVector2<T>& v)
	{
		if (v == ZeroVector)
		{
			return 0.f;
		}
		float radian = FMath::Atan2(-v.y, v.x);
		return FMath::RadianToDegree(radian);
	}

	template<typename T>
	FORCEINLINE TVector2<T> TVector2<T>::DegreeToVector(float angle)
	{
		float radian = -FMath::DegreeToRadian(angle);
		float fsin = FMath::Sin(radian);
		float fcos = FMath::Cos(radian);
		return TVector2<T>(fcos, fsin);
	}

	template<typename T>
	FORCEINLINE TVector2<T> TVector2<T>::RotateVector(float angle, const TVector2<T>& v)
	{
		float radian = FMath::DegreeToRadian(angle);
		float fsin = FMath::Sin(radian);
		float fcos = FMath::Cos(radian);
		return TVector2<T>(v.x * fcos - v.y * fsin, v.x * fsin + v.y * fcos);
	}

	template<typename T>
	FORCEINLINE TVector2<T> TVector2<T>::RotateAround(float angle, const TVector2<T>& center, const TVector2<T>& p)
	{
		return RotateVector(angle, p - center) + center;
	}

	template<typename T>
	FORCEINLINE TVector2<T> TVector2<T>::ProjectVector(const TVector2<T>& u, const TVector2<T>& v)
	{
		float scalar = DotProduct(u, v) * FMath::InvSqrt(v.SizeSquared());  // ����ͶӰ��������������
		return v.GetSafeNormal() * scalar;
	}

	template<typename T>
	const TVector2<T> TVector2<T>::ZeroVector = TVector2<T>();

	template<typename T>
	const TVector2<T> TVector2<T>::UnitVector = TVector2<T>(1, 1);
}
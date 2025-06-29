/**
 * @file	Math.h
 * @brief   ȫ����ѧ�����ⶨ��
 * @author	Arty
 **/

#pragma once
#include <random>
#include <xmmintrin.h>
#include "Macro.h"


constexpr float AE_PI = 3.14159265f;
constexpr float AE_SMALL_NUMBER = 1.e-8f;
constexpr float AE_KINDA_SMALL_NUMBER = 1.e-4f;
constexpr float AE_BIG_NUMBER = 3.4e+38f;
constexpr float AE_EULERS_NUMBER = 2.71828183f;
constexpr float AE_GOLDEN_RATIO = 1.61803399f;


/*----------------------------------
			  ������ѧ�� 
  ----------------------------------*/
struct FMath final
{
	//��ȡ�������������
	static int32 RandInt(int32 lower, int32 upper);

	//��ȡʵ�����������
	static float RandReal(float lower, float upper);

	//��ȡ0~1֮��������
	static double RandPerc();

	//��ȡ����֮��ϴ���
	template<typename T>
	static FORCEINLINE T Max(const T a, const T b)
	{
		return (a > b) ? a : b;
	}

	//��ȡ����֮���С��
	template<typename T>
	static FORCEINLINE T Min(const T a, const T b)
	{
		return (a < b) ? a : b;
	}

	//��ȡ����֮�������
	template<typename T>
	static FORCEINLINE T Max(const T a, const T b, const T c)
	{
		return Max(Max(a, b), Max(a, c));
	}

	//��ȡ����֮����С��
	template<typename T>
	static FORCEINLINE T Min(const T a, const T b, const T c)
	{
		return Min(Min(a, b), Min(a, c));
	}

	//��ȡ����֮����λ��
	template<typename T>
	static FORCEINLINE T Mid(const T a, const T b, const T c)
	{
		return a + b + c - Max(a, b, c) - Min(a, b, c);
	}

	//��ĳ��������ĳ����Χ��
	template<typename T>
	static constexpr FORCEINLINE T Clamp(const T value, const T lower, const T upper)
	{
		return Min(Max(value, Min(lower, upper)), Max(lower, upper));
	}

	//ȡ����ֵ
	template<typename T>
	static FORCEINLINE T Abs(const T value)
	{
		return (value < T(0)) ? -value : value;
	}

	//ȡƽ��
	template<typename T>
	static FORCEINLINE T Square(const T value)
	{
		return value * value;
	}

	//ȡ����
	template<typename T>
	static FORCEINLINE T Cube(const T value)
	{
		return value * value * value;
	}

	//����ȡ�����ĵ���
	static FORCEINLINE float InvSqrt(float inValue)
	{
		if (inValue == 0.f)
		{
			return 0.f;
		}
		const __m128 One = _mm_set_ss(1.0f);
		const __m128 Y0 = _mm_set_ss(inValue);
		const __m128 X0 = _mm_sqrt_ss(Y0);
		const __m128 R0 = _mm_div_ss(One, X0);
		float temp;
		_mm_store_ss(&temp, R0);
		return temp;
	}

	//�Ƿ�ΪС��
	static FORCEINLINE float IsSmallNumber(float value)
	{
		return Abs(value) <= AE_SMALL_NUMBER;
	}

	//���㿪��
	static FORCEINLINE float Sqrt(float value) 
	{ 
		return sqrtf(value); 
	}

	//�����ݷ�
	static FORCEINLINE float Pow(float a, float b) 
	{ 
		return powf(a, b); 
	}

	//e���ݷ�
	static FORCEINLINE float Exp(float value) 
	{ 
		return expf(value);
	}

	//��eΪ��ȡ����
	static FORCEINLINE float Log(float value)
	{
		return log(value);
	}

	//��������ֵ
	static FORCEINLINE float Sin(float value) 
	{
		return sinf(value); 
	}

	//��������ֵ
	static FORCEINLINE float Cos(float value) 
	{
		return cosf(value); 
	}

	//��������ֵ
	static FORCEINLINE float Tan(float value) 
	{ 
		return tanf(value);
	}

	//���㷴����ֵ
	static float Atan2(float y, float x);

	//������ȡģ
	static FORCEINLINE float Fmod(float a, float b)
	{
		if (IsSmallNumber(b))
		{
			return 0.0;
		}
		return fmodf(a, b);
	}

	//������ת��Ϊ�Ƕ�
	static FORCEINLINE float RadianToDegree(float radian)
	{
		return radian * 180 / AE_PI;
	}

	//���Ƕ�ת��Ϊ����
	static FORCEINLINE float DegreeToRadian(float degree)
	{
		return degree * AE_PI / 180;
	}

	//���Ƕȹ淶��(0~360����)
	static FORCEINLINE float NormalizeDegree(float angle)
	{
		float ang = Fmod(angle, 360.0f);
		return ang >= 0 ? ang : ang + 360;
	}


	/**
	 * @brief �������Բ�ֵ
	 * @param[in] a           ԭ��ֵ
	 * @param[in] b           Ŀ����ֵ
	 * @param[in] x           ����ֵ
	 * @return ���ղ�ֵ
	 */
	template <typename T, typename U>
	static constexpr FORCEINLINE T Lerp(const T& a, const T& b, const U& alpha)
	{
		return (T)(a + alpha * (b - a));
	}

	/**
	 * @brief ����ƽ�� Hermite ��ֵ
	 * @param[in] a           �½�
	 * @param[in] b           �Ͻ�
	 * @param[in] x           ����ֵ
	 * @return 0 �� 1 ֮���ƽ����ֵ
	 */
	template<typename T>
	static constexpr T SmoothStep(const T& a, const T& b, const T& x)
	{
		if (x < a)
		{
			return 0;
		}
		else if (x >= b)
		{
			return 1;
		}
		const T interpFraction = (x - a) / (b - a);
		return interpFraction * interpFraction * (3.0f - 2.0f * interpFraction);
	}

private:
	static std::random_device rd;
	static std::mt19937 gen;
};
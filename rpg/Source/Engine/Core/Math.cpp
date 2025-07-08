#include "Math.h"



std::random_device FMath::rd;
std::mt19937 FMath::gen(rd());

int32 FMath::RandInt(int32 lower, int32 upper)
{
    if(lower > upper)
    {
        int32 temp = lower;
        lower = upper;
        upper = temp;
    }
    std::uniform_int_distribution<int32> dis(lower, upper);
    return dis(gen);
}

float FMath::RandReal(float lower, float upper)
{
    if(lower > upper)
    {
        float temp = lower;
        lower = upper;
        upper = temp;
    }
    std::uniform_real_distribution<float> dis(lower, upper);
    return dis(gen);
}

double FMath::RandPerc()
{
    return std::generate_canonical<double, 10>(gen);
}

float FMath::Atan2(float y, float x)
{
	//��ʹ����Ϸ���std ���е� atan2f ������ĳЩ�����Ҳ�᷵�� NaN
	//����������һ�� �ƽ���(minimax approximation) ��ʵ�� atan2f ����
	//�����ԣ��÷������������ 7.2e-7 ���Һ�ʱ��Ϊ std ��汾��һ�� 

	const float absX = FMath::Abs(x);
	const float absY = FMath::Abs(y);
	const bool yAbsBigger = (absY > absX);
	float t0 = yAbsBigger ? absY : absX; 
	float t1 = yAbsBigger ? absX : absY;

	if (t0 == 0.f)
	{
		return 0.f;
	}
		
	float t3 = t1 / t0;
	float t4 = t3 * t3;

	static const float c[7] = 
	{
		+7.2128853633444123e-03f,
		-3.5059680836411644e-02f,
		+8.1675882859940430e-02f,
		-1.3374657325451267e-01f,
		+1.9856563505717162e-01f,
		-3.3324998579202170e-01f,
		+1.0f
	};

	t0 = c[0];
	t0 = t0 * t4 + c[1];
	t0 = t0 * t4 + c[2];
	t0 = t0 * t4 + c[3];
	t0 = t0 * t4 + c[4];
	t0 = t0 * t4 + c[5];
	t0 = t0 * t4 + c[6];
	t3 = t0 * t3;

	t3 = yAbsBigger ? (0.5f * AE_PI) - t3 : t3;
	t3 = (x < 0.0f) ? AE_PI - t3 : t3;
	t3 = (y < 0.0f) ? -t3 : t3;

	return t3;
}
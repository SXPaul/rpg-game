/**
 * @file	Camera.h
 * @brief	2D����������
 * @author	Arty
 **/

#pragma once
#include "SceneComponent.h"



/*----------------------------------
			  ��������
  ----------------------------------*/
class Camera final :public SceneComponent
{
	friend class World;

public:
	virtual void BeginPlay()override;

	//�����������
	void SetMainCamera();

	//��������ƶ�ƽ����
	void SetSmoothness(int32 smooth);

	//���þ�����ֵ
	void SetDistanceThreshold(float threshold);

	//����������ɳ���
	void SetSpringArmLength(float length);

	//�����������ƽ����
	void SetSpringArmSmoothness(int32 smooth);

	//�����
	void ShakeCamera(int32 intensity, int32 decay = 10);

	//��������ɻ���
	void SetRectFrame(const FRect& frame);

	//��ȡ�������λ��
	FVector2D GetVirtualPosition()const;

	//��ȡ����������ɳ���
	float GetVirtualSpringArmLength()const;

private:
	FTransform transform_virtual;//���������������

	FRect frame;//����ɻ��

	float distanceThreshold = 100.f;//������ֵ0`500
	int32 smoothness = 30;//ƽ����0~100

	float shakeIntensity = 0;//��ǿ��0~100
	bool shakeFlag = false;//�𶯱�־λ
	int32 shakeDecay = 5;//��˥��ϵ��1~100
	FVector2D lastShakeVector;//��¼�ϴ���ƫ������

	float springArmLength = 20.f;//���ɳ���1~10000
	float springArmLength_virtual = 100.f;//���ⵯ�ɳ���
	int32 smoothnessForSpringArm = 20;//����ƽ����0~100


	//ƽ������
	float SmoothStep(float x);

	//��ֵ����
	void Calculate();
};
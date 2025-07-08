/**
 * @file	Particle.h
 * @brief	2D����ϵͳ��ʵ��
 * @author	Arty
 **/


#pragma once
#include"SceneComponent.h"
#include"Tools/VisualInterface.h"



/* ���ӷ�����״ */
enum class EParticlePattern :uint8
{
	Center, //���ķ���״
	Line //���Է���״
};

/* ������ʧ���� */
enum class EParticleFadingType :uint8
{
	FadeInAndOut, //����
	ExpandAndShrink //����
};

/* ����������Ϣ */
namespace ArtyEngine
{
	struct FParticleInfo
	{
		FVector2D position;//��������
		int32 index = 0; //��ǰ֡����
		FVector2D velocity; //�ٶ�
		time_point<steady_clock>lastTime;//���Ӵ���ʱ��
		float alpha = 255.f; //͸����
		float size = 1.f;//��С
		float maxSize = 1.f;//��ֵ��С
		float degree = 0.f;//�Ƕ�
		FParticleInfo() { lastTime = steady_clock::now(); }
	};
}



/*----------------------------------
			  �������
  ----------------------------------*/
class ParticleSystem final : public SceneComponent, public LayerInterface, public ImageInterface
{
	std::deque<ArtyEngine::FParticleInfo>particles;
	int32 capacity = 0; //��������
	int32 parNum = 0;//����������Ŀ

	float maxSpeed = 1.f; //���������ٶ�
	float minSpeed = 1.f; //������С���ٶ�
	float graivity = 9.8f; //�������ٶ�

	float lifeCycle = 1.f; //������������
	bool isLoop = true; //�Ƿ�ѭ������
	time_point<steady_clock>lastTime;//���ڼ�¼����
	float interval = 0.1f; //�������
	float fadingInTime = 0; //�����𽥳��ֵ�ʱ��
	float fadingOutTime = 0; //��������ʧ��ʱ��
	EParticleFadingType fadingType = EParticleFadingType::FadeInAndOut;//�����𽥳��ֻ���ʧ������

	IMAGE** images = nullptr;//����֡����
	int32 number = 0; //����֡��
	FVector2D sizeRange; //��С��Χ������ϵ����

	EParticlePattern pattern = EParticlePattern::Center; //���ӷ���״ģʽ
	FVector2D unitVector = FVector2D(0, 1); //���ӷ���λ����

	/* ���ķ���״���Գ�Ա */
	FVector2D radius{};//���⾶
	FVector2D scoop = FVector2D(0, 360);//���䷶Χ

	/* ���Է���״���Գ�Ա */
	float length = 1.f; //���Է��䳤��
	float angle = 0.f; //���Է���Ƕ�
	float offset = 0.f; //���Է���ƫ��
	bool twoWay = false; //���Է��䷽��

	void Produce(); //��������

	void DealImage()override {}

public:
	ParticleSystem() :sizeRange(FVector2D(0.75, 1.25)) { lastTime = steady_clock::now(); }

	//����������Դ
	void Load(std::string name);

	virtual void Update(float deltaTime)override;

	virtual void Render()override;

	//������������
	void SetCapacity(int32 capacity) { this->capacity = capacity; }

	//�������ӷ��������ٶ�
	void SetMaxSpeed(float speed) { this->maxSpeed = speed; }

	//�������ӷ�����С���ٶ�
	void SetMinSpeed(float speed) { this->minSpeed = speed; }

	//������������
	void SetGravity(float graivity) { this->graivity = graivity; }

	//���õ��������������� 
	void SetLifeCycle(float lifeCycle) { this->lifeCycle = lifeCycle; }

	//���������Ƿ�������� 
	void SetIsLoop(bool isLoop) { this->isLoop = isLoop; }

	//���������������
	void SetInterval(float interval) { this->interval = interval; }

	//���������𽥳���ʱ�� 
	void SetFadingInTime(float fadingTime) { this->fadingInTime = fadingTime; }

	//������������ʧʱ�� 
	void SetFadingOutTime(float fadingTime) { this->fadingOutTime = fadingTime; }

	//�������ӽ�����ʧ����
	void SetFadingType(EParticleFadingType fadingType) { this->fadingType = fadingType; }

	//��������ģʽ
	void SetPattern(EParticlePattern pattern) { this->pattern = pattern; }

	/**
	 * @brief ���ô�С��Χ������ϵ����
	 * @param[in] lower			    ��С����
	 * @param[in] upper				�����
	 **/
	void SetSizeRange(float lower, float upper) { sizeRange = {lower,upper}; }

	/**
	 * @brief �������ķ���״����
	 * @param[in] radius			����Բ�������⾶
	 * @param[in] scoop				�������εĽǶȷ�Χ
	 **/
	void SetCenter(FVector2D radius, FVector2D scoop = FVector2D(0, 360));

	/**
	 * @brief �������Է���״����
	 * @param[in] length			�����߶γ���
	 * @param[in] angle	            ���䷽��Ƕ�(�߶η���)
	 * @param[in] offset	        ����ƫ��
	 * @param[in] twoWay	        �Ƿ�Ϊ˫��
	 **/
	void SetLine(float length, float angle, float offset = 0.f, bool twoWay = false);

	virtual void RegisterDontDestroy()override;
};
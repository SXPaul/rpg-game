/**
 * @file	AudioPlayer.h
 * @brief	ý�岥��������
 * @author	Arty
 **/

#pragma once
#include "SceneComponent.h"



 /*----------------------------------
			   ý�岥����
   ----------------------------------*/
class AudioPlayer final :public SceneComponent
{
	DEFINE_SUPER(SceneComponent)

	std::unordered_set<std::string>paths;

	float innerRadius = 0;//��Դ�ھ�
	float outerRadius = 0;//��Դ�⾶
	bool bSpacial = false;//֧�ֿռ�еĲ�����ʱ�俪���ϴ�����
	int32 volume = 1000;//ý��������С����ΧΪ0~1000

	int32 currentVol = 0;
	
public:
	virtual ~AudioPlayer();

	virtual void Update(float deltaTime)override;

	//�Ƿ�֧�ֿռ��
	void SetSpacial(bool spacial) { bSpacial = spacial; }

	//�������⾶�����ھ����⾶��Դ�ݼ�����
	void SetRadius(float inner, float outer) 
	{
		innerRadius = (inner < 0 ? 0 : inner);
		outerRadius = (outer < 0 ? 0 : outer);
	}

	//��ȡ������С
	int32 GetVolume()const { return volume; }

	//����������С
	void SetVolume(int32 vol);

	//��������
	void Play(std::string name, bool repeat = false);

	//����������Դ����ʡ�ڴ棬���ٴβ��Ż����Ľϴ����ܣ�
	void Stop(std::string name);

	//ֹͣ����
	void Close(std::string name);

	//��ͣ����
	void Pause(std::string name);

	//��������
	void Resume(std::string name);

	//��������Ƿ��ڲ���
	bool IsPlaying(std::string name);

private:
	int32 Reflect(int32 x);
};
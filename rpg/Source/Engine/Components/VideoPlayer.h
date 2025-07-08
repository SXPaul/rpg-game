/**
 * @file	VideoPlayer.h
 * @brief	��Ƶ����������
 * @author	Arty
 **/

#pragma once
#include "SceneComponent.h"
#include <dshow.h>

DECLARE_NO_PARAM_MULTICAST_DELEGATE_CLASS(VideoEvent)

 /*----------------------------------
			   ��Ƶ������
   ----------------------------------*/
class VideoPlayer final :public SceneComponent
{
public:
	VideoPlayer();
	~VideoPlayer();

	virtual void Update(float deltaTime)override;

	//������Ƶ��Դ
	void Load(std::string name);
	
	//��ʼ����
	void Play();
	
	//��ͣ����
	void Pause();
	
	//��ֹ����
	void Stop();

	//������Ļ���
	void SetRect(FRect rect);

	VideoEvent OnVideoEnd;
private:
	IGraphBuilder* m_pGraph;
	IMediaControl* m_pControl;
	IVideoWindow* m_pVW;
	IMediaEventEx* m_pEvent;
	FRect renderBox;
};
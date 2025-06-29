/**
 * @file	SpriteRenderer.h
 * @brief	2D��Ⱦ��
 * @author	Arty
 **/

#pragma once
#include"Components/SceneComponent.h"
#include"Tools/VisualInterface.h"




/*----------------------------------
			  ��Ⱦ����2D��
  ----------------------------------*/
class SpriteRenderer final: public SceneComponent, public LayerInterface, public ImageInterface
{
	DEFINE_SUPER(SceneComponent)

	void DealImage()override;

public:
	virtual ~SpriteRenderer();
	virtual void Render()override;
	virtual void Update(float deltaTime)override;

	/**
	 * @brief ʹ��ͼ������һ��
	 * @param[in] duration			һ��Ƶ������ʱ��
	 * @param[in] color	            Ƶ��������˾���ɫ
	 * @param[in] level             �����˾�ʩ�ӳ̶ȣ����Ϊ100����СΪ0��
	 **/
	void Blink(float duration = 0.2f, COLORREF color = BLACK, int32 level = 60);

	//����ͼ����Դ������
	void SaveImage();

	virtual void RegisterDontDestroy()override;

private:
	bool isBlinking = false;
	bool blinkFlag = false;
	float transistionLevel = 0;
	float transistionCoefficient = 0;
	ArtyEngine::FilterInfo blinkFilter;
	Timer* recoverTimerHandle{};
};
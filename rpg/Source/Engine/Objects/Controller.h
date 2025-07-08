/**
 * @file	Controller.h
 * @brief   ��ҿ������ඨ�壬��ÿ�������б�����ڵĶ��󣨲�Ψһ����ͬһʱ��ֻ�ܴ���һ��������������߼�����������ҽ����߼�
 * @author	Arty
 **/


#pragma once
#include"Actor.h"
#include"Components/InputComponent.h"



class Camera;


/*----------------------------------
			 ��ҿ�������
  ----------------------------------*/
class Controller :public Actor
{
	DEFINE_SUPER(Actor)

	InputComponent* inputComponent;
	Camera* camera;

protected:
	virtual void SetupInputComponent(InputComponent* inputComponent) {}

public:
	Controller();

	virtual void BeginPlay() override;

	//���µ�������Ϣ
	void PeekInfo();

	//������������Ϣ
	void PeekInfo_();

	//���������Ϣ
	void MouseTick();

	//��ȡ�����������ϵλ��
	FVector2D GetCursorPosition() const;

	//��ȡ����Ƿ���
	bool IsMouseClicked() const;

	//�Ƿ����κΰ���������
	bool IsAnyKeyPressed() const;

	//�Ƿ��а���������
	bool IsKeyPressed(EKeyCode keycode) const;

	/**
	 * @brief ��ȡ�������λ���������Ϣ�����������ӵ����ײ�壩
	 * @return  FHitResult ��������ϵ���������λ������������Ϣ
	 **/
	FHitResult GetHitResultUnderCursor() const;

	//�����������
	void EnableInput(bool enable);
};
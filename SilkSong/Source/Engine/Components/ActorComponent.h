/**
 * @file	ActorComponent.h
 * @brief	��������Ļ���ActorComponent����
 * @author	Arty
 **/

#pragma once
#include"CoreMinimal.h"
#include"Tools/Timer.h"

class Actor;

DECLARE_NO_PARAM_MULTICAST_DELEGATE_CLASS(ComponentEvent)

/*----------------------------------
			  �������
  ----------------------------------*/
class ActorComponent : public Object, public TimerHandler
{
public:
	virtual ~ActorComponent() {}

	//��ȡ����Ϸ����
	Actor* GetOwner();

	//���ð���Ϸ����
	void SetOwner(Actor* owner);

	//�������
	virtual void Destruct();

	//�������
	virtual void Activate();
	
	//ͣ�����
	virtual void Deactivate();

	//����Ƿ�����
	bool GetEnabled()const { return bIsEnabled; }

	/* ���ʹ���¼� */
	ComponentEvent OnActivated;
	ComponentEvent OnDeactivated;

	//�������ȫ�ֶ���ע��
	virtual void RegisterDontDestroy() {}

protected:
	Actor* pOwner = nullptr;//��������߼�

	bool bIsEnabled = true;//�Ƿ񼤻�
};
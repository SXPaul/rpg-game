/**
 * @file	UserInterface.h
 * @brief   UI��ģ�壬�������ɲ�����uiС����
 * @author	Arty
 **/

#pragma once
#include"Widgets.h"
#include"Tools/Timer.h"


DECLARE_NO_PARAM_MULTICAST_DELEGATE_CLASS(ViewPortEvent)

/*----------------------------------
			    UI�� 
  ----------------------------------*/
class UserInterface : public Object, public TimerHandler
{
	friend Panel;
	friend class WidgetComponent;

	std::unordered_set<Widget*>widgets;
	std::unordered_set<UserInterface*>userInterfaces;

	bool bRemoveFlag = false;

	void BeginPlay()override {}
	void EndPlay()override {}

protected:
	Widget* const rootCanvas = new Widget;

public:
	UserInterface();
	virtual ~UserInterface() { for (auto& widget : widgets)delete widget; }

	virtual void Update(float deltaTime);

	void ShowInfoBoxs();

	void DrawDebugRect();

	//���widgetС������UIģ�����
	template<class T>
	T* AddWidget()
	{
		T* gameWid = new T;
		if (Widget* buf = static_cast<Widget*>(gameWid))
		{
			widgets.insert(buf);
			return gameWid;
		}
		delete gameWid;
		return nullptr;
	}

	//��UI��ӵ��ӿ�
	void AddToViewport();

	//��UI���ӿ���ʱ����
	void HideFromViewport();

	//��UI���ӿ��Ƴ�
	void RemoveFromViewport();

	//��UI������һUI��
	void AttachTo(UserInterface* aim);

	//��UI����һUI���
	void DettachFrom(UserInterface* aim);

	/* �ӿ��¼� */
	ViewPortEvent OnAddedToViewport;
	ViewPortEvent OnHidFromViewport;
	ViewPortEvent OnRemovedFromViewport;

	//ȫ�ֶ���ע��
	void RegisterDontDestroy();
};
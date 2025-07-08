/**
 * @file	Level.h
 * @brief   �ؿ��ඨ�塣һ��Worldͬһʱ�����ҽ���һ���ؿ���һ���ؿ�ͬһʱ��ֻ�ٿ�һ��Controller��
 * @author	Arty
 **/


#pragma once
#include"CoreMinimal.h"
#include"GameplayStatics.h"
#include"Tools/Timer.h"
#include "Player.h"


DECLARE_NO_PARAM_MULTICAST_DELEGATE_CLASS(LevelEvent)

/*----------------------------------
			  ��Ϸ�ؿ�
  ----------------------------------*/
class Level :public Object, public TimerHandler
{
	friend GameplayStatics;

	class Controller* mainController = nullptr;

	std::function<void()> callback;

public:
	Level();

	virtual void BeginPlay()override;

	template<typename T>
	void SetDefaultController()
	{
		callback = [this]() {return mainController = GameplayStatics::CreateObject<T>(); };
	}
	FVector2D GetPosition()
	{
		return ((Player*)mainController)->GetCameraPos();
	}
	LevelEvent OnLevelLoad;
	LevelEvent OnLevelDelete;
};
#include "PlayerAnimator.h"
#include "Player.h"
#include "GameplayStatics.h"
#include "GameModeHelper.h"


PlayerAnimator::PlayerAnimator()
{
	idle.Load("player_idle");
	idle.SetInterval(0.1f);
	// �����ж������뵽������������
	Insert("idle", idle);
	// ���ó�ʼ�����ڵ�Ϊ����״̬
	SetNode("idle");
	//walk.Load("player_walk");
	//walk.SetInterval(0.1f);
	//walkstart.Load("player_walkstart");
	//walkstart.SetInterval(0.04f);
	//walkend.Load("player_walkend");
	//walkend.SetInterval(0.06f);

}

void PlayerAnimator::BeginPlay()
{
	Animator::BeginPlay();

}
#include "PlayerAnimator.h"
#include "Player.h"
#include "GameplayStatics.h"
#include "GameModeHelper.h"


PlayerAnimator::PlayerAnimator()
{
	idle.Load("player_idle");
	idle.SetInterval(0.1f);
	// 将空闲动画插入到动画管理器中
	Insert("idle", idle);
	// 设置初始动画节点为空闲状态
	SetNode("idle");
	run.Load("player_run");
	run.SetInterval(0.1f);
	Insert("run", run);
	AddParamater("walkingSpeed", ParamType::Float);
	//walkstart.Load("player_walkstart");
	//walkstart.SetInterval(0.04f);
	//walkend.Load("player_walkend");
	//walkend.SetInterval(0.06f);

}

void PlayerAnimator::BeginPlay()
{
	Animator::BeginPlay();
	idle_to_runstart.Init(idle, run);
	idle_to_runstart.AddCondition(AnimTransition::Float{ "walkingSpeed",1.f,TransitionComparison::GreaterEqual });
	run_to_idle.Init(run, idle);
	run_to_idle.AddCondition(AnimTransition::Float{ "walkingSpeed",0.f,TransitionComparison::LessEqual });
}
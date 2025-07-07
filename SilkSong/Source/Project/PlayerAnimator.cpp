#include "PlayerAnimator.h"
#include "Player.h"
#include "GameplayStatics.h"
#include "GameModeHelper.h"


PlayerAnimator::PlayerAnimator()
{
	idle.Load("player_idle");
	run.Load("player_run");
	jump1.Load("player_jump_1");
	jump2.Load("player_jump_2");
	jump_falling.Load("player_jump_falling");
	die.Load("player_die");
	dead.Load("player_dead");
	attack1.Load("player_attack1");
	attack_up.Load("player_attack2");


	idle.SetInterval(0.1f);
	run.SetInterval(0.1f);
	jump1.SetInterval(0.1f);
	jump2.SetInterval(0.1f);
	jump_falling.SetInterval(0.1f);
	die.SetInterval(0.1f);
	dead.SetInterval(0.1f);

	Insert("idle", idle);
	Insert("run", run);
	Insert("player_jump_1", jump1);
	Insert("player_jump_2", jump2);
	Insert("player_jump_falling", jump_falling);
	Insert("player_die", die);
	Insert("player_dead", dead); 
	Insert("player_attack1", attack1);
	Insert("player_attack2", attack_up);


	SetNode("idle");

	AddParamater("walkingSpeed", ParamType::Float);
	AddParamater("jumpSpeed", ParamType::Float);
	AddParamater("isToRun", ParamType::Bool);

}

void PlayerAnimator::BeginPlay()
{
	Animator::BeginPlay();
	idle_to_runstart.Init(idle, run);
	run_to_idle.Init(run, idle);
	idle_to_jump1.Init(idle, jump1);
	idle_to_jump2.Init(idle, jump2);
	run_to_jump1.Init(run, jump1);
	run_to_jump2.Init(run, jump2);
	//jump2_to_idle.Init(jump2,idle);
	//jump1_to_idle.Init(jump1,idle);
	//jump2_to_run.Init(jump2,run);
	//jump1_to_run.Init(jump1,run);
	jump1_to_falling.Init(jump1, jump_falling);
	jump1_to_falling.Init(jump2, jump_falling);
	//jump1_to_idle.AddCondition(AnimTransition::Bool{ "isToRun",false });
	//jump2_to_idle.AddCondition(AnimTransition::Bool{ "isToRun",false });
	//jump1_to_run.AddCondition(AnimTransition::Bool{ "isToRun",true });
	//jump2_to_run.AddCondition(AnimTransition::Bool{ "isToRun",true });
	
	idle_to_jump1.AddCondition(AnimTransition::Float{ "jumpSpeed",-1.f,TransitionComparison::LessEqual });
	idle_to_jump2.AddCondition(AnimTransition::Float{ "jumpSpeed",-2.f,TransitionComparison::LessEqual });
	run_to_jump1.AddCondition(AnimTransition::Float{ "jumpSpeed",-1.f,TransitionComparison::LessEqual });
	run_to_jump2.AddCondition(AnimTransition::Float{ "jumpSpeed",-2.f,TransitionComparison::LessEqual });
	idle_to_runstart.AddCondition(AnimTransition::Float{ "walkingSpeed",1.f,TransitionComparison::GreaterEqual });
	run_to_idle.AddCondition(AnimTransition::Float{ "walkingSpeed",0.f,TransitionComparison::LessEqual });
}
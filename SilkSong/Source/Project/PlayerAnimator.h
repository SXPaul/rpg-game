#pragma once
#include"Components/Animator.h"



class PlayerAnimator : public Animator
{
public:
	PlayerAnimator();

	void BeginPlay()override;

	//AnimationDelegate wetWalkEffect;
	//AnimationDelegate dashEffect;
	//AnimationDelegate cureEffect;
	//AnimationDelegate hurtPause;
	//AnimationDelegate dartSpawn;
	//AnimationDelegate needleSpawn;
	//AnimationDelegate needleSpawn_;
	//AnimationDelegate grabFinished;
	//AnimationDelegate downAttackSpawn;
	//AnimationDelegate dieShake;
	//AnimationDelegate leaveStart;
	//AnimationDelegate defendPause;
	//AnimationDelegate defendAttack;

private:
	Animation idle;
	Animation run;
	Animation jump1;
	Animation jump2;
	Animation jump_falling;
	Animation die;
	Animation dead;

	AnimEdge idle_to_runstart;
	AnimEdge run_to_idle;
	AnimEdge idle_to_jump1;
	AnimEdge idle_to_jump2;
	AnimEdge run_to_jump1;
	AnimEdge run_to_jump2;
	AnimEdge jump1_to_falling;
	AnimEdge jump2_to_falling;
	//AnimEdge jump2_to_idle;
	//AnimEdge jump1_to_idle;
	//AnimEdge jump2_to_run;
	//AnimEdge jump1_to_run;



	//AnimEdge idle_to_walkstart;
};
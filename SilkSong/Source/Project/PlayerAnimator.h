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
	AnimEdge idle_to_runstart;
	AnimEdge run_to_idle;

	//AnimEdge idle_to_walkstart;
};
#pragma once
#include "Enemy.h"


class Enemy1 :public Enemy
{
	DEFINE_SUPER(Enemy)

public:
	Enemy1();

	virtual void BeginPlay()override;

	virtual void Update(float deltaTime)override;

	virtual void ExecuteDamageTakenEvent(FDamageCauseInfo extraInfo)override;

protected:
	virtual void SpawnGeos()override;

	virtual void Die()override;

private:
	Animation idle;
	//Animation turn;
	Animation react;
	Animation walk;
	Animation die;
	AnimEdge idle_to_react;
	//AnimEdge turn_to_idle;
	//AnimEdge turn_to_chase;
	AnimEdge react_to_walk;
	AnimEdge walk_to_die;

	bool bChasing = false;
};

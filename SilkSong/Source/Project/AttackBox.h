#pragma once
#include "Player.h"
#include "Damagable.h"


class AttackBox :public Actor, public IDamagable
{
	DEFINE_SUPER(Actor)

public:
	AttackBox();

	void Init(AttackDirection direction, int32 damage = 3);

	void OnOverlap(class Collider* hitComp, Collider* otherComp, Actor* otherActor);

	void OnEndOverlap(class Collider* hitComp, Collider* otherComp, Actor* otherActor);

	void SetSize(FVector2D size);

	void SetLocalPosition(FVector2D pos);

	virtual FDamageCauseInfo TakeDamage(IDamagable* damageCauser, float baseValue, EDamageType damageType)override { return{}; }

	virtual void ExecuteDamageDealtEvent(FDamageCauseInfo extraInfo)override {}

	virtual void ExecuteDamageTakenEvent(FDamageCauseInfo extraInfo)override {}

private:
	class BoxCollider* box;
	Timer AttackTimerHandle;
	Timer DestroyTimerHandle;
	AttackDirection direction;
	int32 damage;
};
#pragma once
#include "Enemy.h"

enum class EnemyState {
	Idle,
	Chasing,
	Attacking
};
class Enemy1 :public Enemy
{
	DEFINE_SUPER(Enemy)

public:
	Enemy1();

	virtual void BeginPlay()override;

	virtual void Update(float deltaTime)override;

	virtual void ExecuteDamageTakenEvent(FDamageCauseInfo extraInfo)override;
	// 添加设置追击边界的函数
	void SetChaseBoundary(FVector2D minBoundary, FVector2D maxBoundary);
protected:
	virtual void SpawnGeos()override;

	virtual void Die()override;

	// 新增成员变量
	EnemyState currentState;  // 敌人当前状态
	float sightRange;         // 敌人的视野范围
	float attackRange;        // 敌人的攻击范围
	float moveSpeed;          // 敌人的移动速度
	float attackCooldown;     // 攻击冷却时间
	float currentCooldown;    // 当前冷却时间

	// 新增方法声明
	void CheckPlayerInRange();
	void ChasePlayer(float deltaTime);
	void AttackPlayer();
	// 追击边界
	FVector2D chaseMinBoundary;
	FVector2D chaseMaxBoundary;

private:
	Animation idle;
	//Animation turn;
	Animation react;
	Animation walk;
	Animation die;
	Animation attack;
	AnimEdge idle_to_react;
	//AnimEdge turn_to_idle;
	//AnimEdge turn_to_chase;
	AnimEdge react_to_walk;
	AnimEdge walk_to_die;
	AnimEdge idle_to_attack;
	AnimEdge walk_to_idle;
	AnimEdge attack_to_idle;
	AnimEdge attack_to_walk;
	AnimEdge attack_to_die;

	bool bChasing = false;
};

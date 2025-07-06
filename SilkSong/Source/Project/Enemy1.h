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
	// �������׷���߽�ĺ���
	void SetChaseBoundary(FVector2D minBoundary, FVector2D maxBoundary);
protected:
	virtual void SpawnGeos()override;

	virtual void Die()override;

	// ������Ա����
	EnemyState currentState;  // ���˵�ǰ״̬
	float sightRange;         // ���˵���Ұ��Χ
	float attackRange;        // ���˵Ĺ�����Χ
	float moveSpeed;          // ���˵��ƶ��ٶ�
	float attackCooldown;     // ������ȴʱ��
	float currentCooldown;    // ��ǰ��ȴʱ��

	// ������������
	void CheckPlayerInRange();
	void ChasePlayer(float deltaTime);
	void AttackPlayer();
	// ׷���߽�
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

#pragma once
#include "Enemy.h"
#include "Boss1UI.h"

enum class EnemyState {
	Idle,
	Chasing,
	Attacking,
	Hurt
};
class NightBorne :public Enemy
{
	DEFINE_SUPER(Enemy)

public:
	NightBorne();

	virtual void BeginPlay()override;

	virtual void Update(float deltaTime)override;

	virtual void ExecuteDamageTakenEvent(FDamageCauseInfo extraInfo)override;
	// �������׷���߽�ĺ���
	void SetChaseBoundary(FVector2D minBoundary, FVector2D maxBoundary);

	void SetSightRange(float r);
	void SetMoveSpeed(float r);
	void SetAttackCooldown(float r);
protected:
	virtual void SpawnGeos()override;

	virtual void Die()override;
	void StartHurtAnimation();
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
	void AdjustColliderOnDeath();
	class Boss1UI* ui;
	Animation idle;
	Animation hurt;
	Animation run;
	Animation die;
	Animation attack;

	AnimEdge idle_to_run;
	AnimEdge idle_to_attack;
	//AnimEdge run_to_die;
	AnimEdge run_to_idle;
	AnimEdge attack_to_idle;
	//AnimEdge attack_to_run;
	//AnimEdge attack_to_die;
	AnimEdge hurt_to_idle;

	bool bHurt=false;
	bool bChasing = false;
	float attackDuration = 0.8f; // ������������ʱ�䣨�룩
	float attackTimer = 0.0f;    // ������ʱ��
	bool isAttacking = false;    // �Ƿ����ڹ���

	float maxHealth = 0.0f;           // ���Ѫ��
	float healthThreshold1 = 0.0f;    // ��һ����ֵ��2/3Ѫ����
	float healthThreshold2 = 0.0f;    // �ڶ�����ֵ��1/3Ѫ����
	bool hasTriggeredThreshold1 = false; // �Ƿ��Ѵ�����һ����ֵ
	bool hasTriggeredThreshold2 = false; // �Ƿ��Ѵ����ڶ�����ֵ

	bool isHurt = false;              // �Ƿ���������
	float hurtDuration = 3.0f;        // ���˶�������ʱ�䣨�룩
	float hurtTimer = 0.0f;           // ���˼�ʱ��

	float deathAnimationDuration = 1.2f; // ������������ʱ�䣨�룩�������ʵ�ʶ������ȵ���
	float deathTimer = 0.0f;            // ������ʱ��
	bool isDeathAnimationFinished = false; // ���������Ƿ񲥷����
};

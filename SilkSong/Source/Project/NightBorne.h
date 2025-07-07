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
	// 添加设置追击边界的函数
	void SetChaseBoundary(FVector2D minBoundary, FVector2D maxBoundary);

	void SetSightRange(float r);
	void SetMoveSpeed(float r);
	void SetAttackCooldown(float r);
protected:
	virtual void SpawnGeos()override;

	virtual void Die()override;
	void StartHurtAnimation();
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
	float attackDuration = 0.8f; // 攻击动画持续时间（秒）
	float attackTimer = 0.0f;    // 攻击计时器
	bool isAttacking = false;    // 是否正在攻击

	float maxHealth = 0.0f;           // 最大血量
	float healthThreshold1 = 0.0f;    // 第一个阈值（2/3血量）
	float healthThreshold2 = 0.0f;    // 第二个阈值（1/3血量）
	bool hasTriggeredThreshold1 = false; // 是否已触发第一个阈值
	bool hasTriggeredThreshold2 = false; // 是否已触发第二个阈值

	bool isHurt = false;              // 是否正在受伤
	float hurtDuration = 3.0f;        // 受伤动画持续时间（秒）
	float hurtTimer = 0.0f;           // 受伤计时器

	float deathAnimationDuration = 1.2f; // 死亡动画持续时间（秒），需根据实际动画长度调整
	float deathTimer = 0.0f;            // 死亡计时器
	bool isDeathAnimationFinished = false; // 死亡动画是否播放完毕
};

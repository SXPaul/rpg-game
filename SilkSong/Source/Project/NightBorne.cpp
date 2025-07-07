#include "NightBorne.h"
//#include "Geo.h"
#include "GameplayStatics.h"
#include "PropertyComponent.h"
#include "Components/RigidBody.h"
#include "Components/Collider.h"
#include "Player.h"
//#include "SilkParticle.h"
#include "Components/SpriteRenderer.h"
#include "GameModeHelper.h"
#include "EnemyAtkBox.h"

NightBorne::NightBorne()
{
	idle.Load("NightBorne_idle");
	run.Load("NightBorne_run");
	die.Load("NightBorne_die");
	attack.Load("NightBorne_attack");
	hurt.Load("NightBorne_hurt");
	idle.SetInterval(0.12f);
	run.SetInterval(0.1f);
	die.SetInterval(0.1f);
	hurt.SetInterval(0.05f);
	attack.SetInterval(0.05f);
	die.SetLooping(false);
	//attack.SetLooping(false);
	idle_to_run.Init(idle, run);
	idle_to_run.AddCondition(AnimTransition::Bool{ "chasing",true });
	idle_to_attack.Init(idle, attack);
	idle_to_attack.AddCondition(AnimTransition::Bool{ "canAttack",true });
	run_to_idle.Init(run, idle);
	run_to_idle.AddCondition(AnimTransition::Bool{ "chasing",false });
	attack_to_idle.Init(attack, idle);
	attack_to_idle.AddCondition(AnimTransition::Bool{ "chasing",false });
	attack_to_idle.AddCondition(AnimTransition::Bool{ "canAttack",false });
	hurt_to_idle.Init(hurt, idle);
	hurt_to_idle.AddCondition(AnimTransition::Bool{ "hurt",false });
	ani->Insert("idle", idle);
	ani->Insert("run", run);
	ani->Insert("die", die);
	ani->Insert("attack", attack);
	ani->Insert("hurt", hurt);
	ani->SetNode("idle");

	ani->AddParamater("chasing", ParamType::Bool);
	ani->AddParamater("canAttack", ParamType::Bool);
	ani->AddParamater("hurt", ParamType::Bool);
	// 初始化新增成员变量
	currentState = EnemyState::Idle;
	sightRange = 1000.f;  // 视野范围
	attackRange = 80.f; // 攻击范围
	moveSpeed = 100.f;   // 移动速度
	attackCooldown = 1.f; // 攻击冷却时间
	currentCooldown = 0.f;
	// 初始化追击边界
	chaseMinBoundary = FVector2D::ZeroVector;
	chaseMaxBoundary = FVector2D::ZeroVector;
	box->SetSize({ 95,95 });
	box->SetLocalPosition({ 3, 30 });

}

void NightBorne::BeginPlay()
{
	Super::BeginPlay();

	property->SetMaxHealth(100);
	property->AddHealth(100);
	// 初始化血量阈值
	maxHealth = property->GetMaxHealth();
	healthThreshold1 = maxHealth * 2.0f / 3.0f;
	healthThreshold2 = maxHealth * 1.0f / 3.0f;
	hasTriggeredThreshold1 = false;
	hasTriggeredThreshold2 = false;


	rigid->SetGravityEnabled(true);
	rigid->SetLinearDrag(1.5f);
}

void NightBorne::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (!IsDead() && GetWorldPosition().y > 1080)
	{
		property->AddHealth(-9999);
		GameplayStatics::PlayCameraShake(4);
		render->Blink(0.3f, WHITE, 100);
		rigid->AddImpulse({ 0,-500 });
		Die();
	}

	if (IsDead() || !player) { 
		// 死亡状态处理
		if (!isDeathAnimationFinished) {
			deathTimer -= deltaTime;
			if (deathTimer <= 0.0f) {
				isDeathAnimationFinished = true;
				AdjustColliderOnDeath();
			}
		}
		return; 
	}

	if (property->GetHealth() <= 0) {
		Die();
		return;
	}

	if (isAttacking) {
		attackTimer -= deltaTime;
		if (attackTimer <= 0.0f) {
			isAttacking = false;
			ani->SetBool("canAttack", false);
		}
		return;
	}
		float currentHealth = property->GetHealth();
		// 检查是否触发阈值
		if (!hasTriggeredThreshold1 && currentHealth <= healthThreshold1) {
			StartHurtAnimation();
			hasTriggeredThreshold1 = true;
		}
		else if (!hasTriggeredThreshold2 && currentHealth <= healthThreshold2) {
			StartHurtAnimation();
			hasTriggeredThreshold2 = true;
		}

	// 更新受伤状态
	if (isHurt) {
		hurtTimer -= deltaTime;
		if (hurtTimer <= 0.0f) {
			isHurt = false;
			ani->SetBool("hurt", false);
			ani->SetNode("idle");
			// 恢复正常状态（根据玩家位置决定）
			CheckPlayerInRange();
		}
		return; // 受伤期间不执行其他逻辑
	}



	// 更新攻击冷却时间
	if (currentCooldown > 0.f) {
		currentCooldown -= deltaTime;
	}

	// 仅在非攻击状态下检查玩家范围
	if (!isAttacking) {
		CheckPlayerInRange();
	}
	// 根据当前状态执行相应逻辑
	switch (currentState) {
	case EnemyState::Chasing:
		ChasePlayer(deltaTime);
		break;
	case EnemyState::Attacking:
		// 攻击逻辑可以在动画事件中处理，这里暂时不做额外处理
		break;
	case EnemyState::Hurt:
		// 受伤状态下不执行其他逻辑
		break;
	default:
		break;
	}
}


void NightBorne::ExecuteDamageTakenEvent(FDamageCauseInfo extraInfo)
{
	//Super::ExecuteDamageTakenEvent(extraInfo);

	if (!extraInfo.bIsValid)
	{
		return;
	}

	Actor* causer = Cast<Actor>(extraInfo.damageCauser);
	CHECK_PTR(causer)
		FVector2D normal = (GetWorldPosition() - causer->GetWorldPosition()).GetSafeNormal();
	float delta_x = causer->GetWorldPosition().x - GetWorldPosition().x;
	normal.y = FMath::Clamp(normal.y, -0.2f, -1.f);

	rigid->AddImpulse(normal * 350.f);
	// 检测血量阈值
	float currentHealth = property->GetHealth();
	if (currentHealth <= 0) {
		rigid->SetAngularVelocity(200 * (delta_x > 0 ? 1.f : -1.f) * GetWorldScale().x);
		Die();
	}
	else {
		// 检查是否触发阈值
		if (!hasTriggeredThreshold1 && currentHealth <= healthThreshold1) {
			StartHurtAnimation();
			hasTriggeredThreshold1 = true;
		}
		else if (!hasTriggeredThreshold2 && currentHealth <= healthThreshold2) {
			StartHurtAnimation();
			hasTriggeredThreshold2 = true;
		}
	}
	//if (property->GetHealth() <= 0)
	//{
	//	rigid->SetAngularVelocity(200 * (delta_x > 0 ? 1.f : -1.f) * GetWorldScale().x);
	//}
}

// 开始受伤动画
void NightBorne::StartHurtAnimation() {
	isHurt = true;
	hurtTimer = hurtDuration;
	currentState = EnemyState::Hurt; // 假设添加了Hurt状态
	ani->SetBool("hurt", true);
	ani->SetNode("hurt");

	// 停止移动
	rigid->SetVelocity(FVector2D::ZeroVector);
}

void NightBorne::SetSightRange(float r)
{
	sightRange = r;
}


void NightBorne::SetMoveSpeed(float r)
{
	moveSpeed = r;
}

void NightBorne::SetAttackCooldown(float r)
{
	attackCooldown = r;
}

void NightBorne::SpawnGeos()
{
	//for (int i = 0; i < 2; i++)
	//{
	//	GameplayStatics::CreateObject<Geo>(GetWorldPosition())->Init("1geo", 1);
	//}
}

void NightBorne::Die()
{
	Super::Die();

	ani->SetNode("die");
	ani->SetBool("chasing", false);
	ani->SetBool("canAttack", false);
	ani->SetBool("hurt", false);
	rigid->SetGravityEnabled(true);
	// 启动死亡计时器
	deathTimer = deathAnimationDuration;
	isDeathAnimationFinished = false;
}

// 死亡后调整碰撞箱
void NightBorne::AdjustColliderOnDeath() {
	if (box) {
		box->SetSize({ 10, 10 });
		box->SetLocalPosition({ -35, 10 }); // 调整位置
	}
}

//void Enemy::OnOverlap(Collider* hitComp, Collider* otherComp, Actor* otherActor)
//{
//
//}
void NightBorne::CheckPlayerInRange() {
	if (player && !isAttacking) {
		FVector2D enemyPos = GetWorldPosition();
		FVector2D playerPos = player->GetWorldPosition();
		float distance = FVector2D::Distance(enemyPos, playerPos);

		if (distance <= sightRange) {
			if (distance <= attackRange) {
				if (bChasing) {
					bChasing = false;
					ani->SetBool("chasing", false);
					ani->SetNode("idle");
				}
				else {
					if (currentCooldown <= 0.f) {
						AttackPlayer();
					}
				}
				currentState = EnemyState::Attacking;
			}
			else {
				ani->SetBool("canAttack", false);
				if (enemyPos.x >= chaseMinBoundary.x && enemyPos.x <= chaseMaxBoundary.x) {
					bChasing = true;
					if (currentState == EnemyState::Attacking) {
						ani->SetNode("idle");
					}
					currentState = EnemyState::Chasing;
				}
				else {
					bChasing = false;
					currentState = EnemyState::Idle;
					ani->SetBool("chasing", false);
					ani->SetNode("idle");
				}
			}
		}
		else {
			ani->SetBool("chasing", false);
			bChasing = false;
			currentState = EnemyState::Idle;
			ani->SetBool("canAttack", false);

		}
	}
}
void NightBorne::ChasePlayer(float deltaTime) {
	if (player) {
		ani->SetBool("chasing", true);
		FVector2D enemyPos = GetWorldPosition();
		FVector2D playerPos = player->GetWorldPosition();
		FVector2D direction = (playerPos - enemyPos).GetSafeNormal();


		// 根据玩家位置调整敌人朝向
		if (direction.x > 0) {
			SetLocalScale(FVector2D(1.f, GetLocalScale().y));
		}
		else {
			SetLocalScale(FVector2D(-1.f, GetLocalScale().y));
		}
		// 移动敌人
		if (direction.x > 0) {
			if (enemyPos.x + moveSpeed > chaseMaxBoundary.x) {
				{
					rigid->SetVelocity({ direction.x * (chaseMaxBoundary.x - enemyPos.x) ,0 });
				}
			}
			else {
				rigid->SetVelocity({ direction.x * moveSpeed,0 });
			}
		}
		else {
			if (enemyPos.x - moveSpeed < chaseMinBoundary.x) {
				rigid->SetVelocity({ direction.x * (enemyPos.x - chaseMinBoundary.x),0 });
			}
			else {
				rigid->SetVelocity({ direction.x * moveSpeed,0 });
			}
		}
	}
}

void NightBorne::AttackPlayer() {
	// 播放攻击动画
	ani->SetBool("canAttack", true);
	//property->AddHealth(-40);

	isAttacking = true;
	attackTimer = attackDuration;
	// 创建攻击框
	EnemyAtkBox* attackBox = GameplayStatics::CreateObject<EnemyAtkBox>();
	attackBox->SetSize({ 120,150 });
	attackBox->AttachTo(this);
	// 根据敌人朝向设置攻击框位置

	FVector2D enemyPos = GetWorldPosition();
	FVector2D playerPos = player->GetWorldPosition();
	FVector2D direction = (playerPos - enemyPos).GetSafeNormal();

	//FVector2D attackBoxOffset =direction.x > 0 ? FVector2D(100, 0) : FVector2D(-300, 0);
	FVector2D attackBoxOffset = FVector2D(50, 30);
	attackBox->SetLocalPosition(attackBoxOffset);
	attackBox->Init(direction.x > 0 ? AttackDirection::Right : AttackDirection::Left, 1); // 假设攻击力为3


	// 重置攻击冷却时间
	currentCooldown = attackCooldown;
}

void NightBorne::SetChaseBoundary(FVector2D minBoundary, FVector2D maxBoundary)
{
	chaseMinBoundary = minBoundary;
	chaseMaxBoundary = maxBoundary;
}
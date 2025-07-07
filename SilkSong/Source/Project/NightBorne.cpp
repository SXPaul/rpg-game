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
	// ��ʼ��������Ա����
	currentState = EnemyState::Idle;
	sightRange = 1000.f;  // ��Ұ��Χ
	attackRange = 80.f; // ������Χ
	moveSpeed = 100.f;   // �ƶ��ٶ�
	attackCooldown = 1.f; // ������ȴʱ��
	currentCooldown = 0.f;
	// ��ʼ��׷���߽�
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
	// ��ʼ��Ѫ����ֵ
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
		// ����״̬����
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
		// ����Ƿ񴥷���ֵ
		if (!hasTriggeredThreshold1 && currentHealth <= healthThreshold1) {
			StartHurtAnimation();
			hasTriggeredThreshold1 = true;
		}
		else if (!hasTriggeredThreshold2 && currentHealth <= healthThreshold2) {
			StartHurtAnimation();
			hasTriggeredThreshold2 = true;
		}

	// ��������״̬
	if (isHurt) {
		hurtTimer -= deltaTime;
		if (hurtTimer <= 0.0f) {
			isHurt = false;
			ani->SetBool("hurt", false);
			ani->SetNode("idle");
			// �ָ�����״̬���������λ�þ�����
			CheckPlayerInRange();
		}
		return; // �����ڼ䲻ִ�������߼�
	}



	// ���¹�����ȴʱ��
	if (currentCooldown > 0.f) {
		currentCooldown -= deltaTime;
	}

	// ���ڷǹ���״̬�¼����ҷ�Χ
	if (!isAttacking) {
		CheckPlayerInRange();
	}
	// ���ݵ�ǰ״ִ̬����Ӧ�߼�
	switch (currentState) {
	case EnemyState::Chasing:
		ChasePlayer(deltaTime);
		break;
	case EnemyState::Attacking:
		// �����߼������ڶ����¼��д���������ʱ�������⴦��
		break;
	case EnemyState::Hurt:
		// ����״̬�²�ִ�������߼�
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
	// ���Ѫ����ֵ
	float currentHealth = property->GetHealth();
	if (currentHealth <= 0) {
		rigid->SetAngularVelocity(200 * (delta_x > 0 ? 1.f : -1.f) * GetWorldScale().x);
		Die();
	}
	else {
		// ����Ƿ񴥷���ֵ
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

// ��ʼ���˶���
void NightBorne::StartHurtAnimation() {
	isHurt = true;
	hurtTimer = hurtDuration;
	currentState = EnemyState::Hurt; // ���������Hurt״̬
	ani->SetBool("hurt", true);
	ani->SetNode("hurt");

	// ֹͣ�ƶ�
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
	// ����������ʱ��
	deathTimer = deathAnimationDuration;
	isDeathAnimationFinished = false;
}

// �����������ײ��
void NightBorne::AdjustColliderOnDeath() {
	if (box) {
		box->SetSize({ 10, 10 });
		box->SetLocalPosition({ -35, 10 }); // ����λ��
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


		// �������λ�õ������˳���
		if (direction.x > 0) {
			SetLocalScale(FVector2D(1.f, GetLocalScale().y));
		}
		else {
			SetLocalScale(FVector2D(-1.f, GetLocalScale().y));
		}
		// �ƶ�����
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
	// ���Ź�������
	ani->SetBool("canAttack", true);
	//property->AddHealth(-40);

	isAttacking = true;
	attackTimer = attackDuration;
	// ����������
	EnemyAtkBox* attackBox = GameplayStatics::CreateObject<EnemyAtkBox>();
	attackBox->SetSize({ 120,150 });
	attackBox->AttachTo(this);
	// ���ݵ��˳������ù�����λ��

	FVector2D enemyPos = GetWorldPosition();
	FVector2D playerPos = player->GetWorldPosition();
	FVector2D direction = (playerPos - enemyPos).GetSafeNormal();

	//FVector2D attackBoxOffset =direction.x > 0 ? FVector2D(100, 0) : FVector2D(-300, 0);
	FVector2D attackBoxOffset = FVector2D(50, 30);
	attackBox->SetLocalPosition(attackBoxOffset);
	attackBox->Init(direction.x > 0 ? AttackDirection::Right : AttackDirection::Left, 1); // ���蹥����Ϊ3


	// ���ù�����ȴʱ��
	currentCooldown = attackCooldown;
}

void NightBorne::SetChaseBoundary(FVector2D minBoundary, FVector2D maxBoundary)
{
	chaseMinBoundary = minBoundary;
	chaseMaxBoundary = maxBoundary;
}
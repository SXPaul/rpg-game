#include "Enemy1.h"
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

Enemy1::Enemy1()
{
	idle.Load("Enemy1_idle");
	idle.SetInterval(0.1f);
	//turn.Load("fly_turn");
	//turn.SetInterval(0.1f);
	react.Load("Enemy1_react");
	react.SetInterval(0.08f);
	walk.Load("Enemy1_walk");
	walk.SetInterval(0.08f);
	die.Load("Enemy1_dead");
	die.SetInterval(0.1f);
	die.SetLooping(false);
	attack.Load("Enemy1_attack");
	react.SetInterval(0.05f);
	attack.SetInterval(0.05f);

	attack_to_idle.Init(attack, idle);
	attack_to_idle.AddCondition(AnimTransition::Bool{ "chasing",false });
	idle_to_react.Init(idle, react);
	idle_to_react.AddCondition(AnimTransition::Bool{ "chasing",true });
	//turn_to_idle.Init(turn, idle);
	//turn_to_chase.Init(turn, chase);
	//turn_to_chase.AddCondition(AnimTransition::Bool{ "chasing",true });
	react_to_walk.Init(react, walk);
	walk_to_idle.Init(walk, idle);
	walk_to_idle.AddCondition(AnimTransition::Bool{ "chasing",false });
	idle_to_attack.Init(idle, attack);
	idle_to_attack.AddCondition(AnimTransition::Bool{ "canAttack",true });
	attack_to_idle.Init(attack, idle);
	attack_to_idle.AddCondition(AnimTransition::Bool{ "canAttack",false});

	ani->Insert("idle", idle);
	//ani->Insert("turn", turn);
	ani->Insert("react", react	);
	ani->Insert("walk", walk);
	ani->Insert("die", die);
	ani->Insert("attack", attack);
	ani->SetNode("idle");

	ani->AddParamater("chasing", ParamType::Bool);
	ani->AddParamater("canAttack", ParamType::Bool);
	// ��ʼ��������Ա����
	currentState = EnemyState::Idle;
	sightRange = 300;  // ��Ұ��Χ
	attackRange = 30.f; // ������Χ
	moveSpeed =80.f;   // �ƶ��ٶ�
	attackCooldown = 1.f; // ������ȴʱ��
	currentCooldown = 0.f;
	// ��ʼ��׷���߽�
	chaseMinBoundary = FVector2D::ZeroVector;
	chaseMaxBoundary = FVector2D::ZeroVector;
	box->SetSize({ 44,66 });
}

void Enemy1::BeginPlay()
{
	Super::BeginPlay();

	property->SetMaxHealth(5);
	property->AddHealth(5);

	rigid->SetGravityEnabled(true);
	rigid->SetLinearDrag(1.5f);
}

void Enemy1::Update(float deltaTime)
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
		return;
	}
	// ���¹�����ȴʱ��
	if (currentCooldown > 0.f) {
		currentCooldown -= deltaTime;
	}

	// �������Ƿ��ڷ�Χ��
	CheckPlayerInRange();

	// ���ݵ�ǰ״ִ̬����Ӧ�߼�
	switch (currentState) {
	case EnemyState::Chasing:
		ChasePlayer(deltaTime);
		break;
	case EnemyState::Attacking:
		// �����߼������ڶ����¼��д���������ʱ�������⴦��
		break;
	default:
		break;
	}
}

void Enemy1::ExecuteDamageTakenEvent(FDamageCauseInfo extraInfo)
{
	Super::ExecuteDamageTakenEvent(extraInfo);

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
	if (property->GetHealth() <= 0)
	{
		rigid->SetAngularVelocity(200 * (delta_x > 0 ? 1.f : -1.f) * GetWorldScale().x);
	}
}

void Enemy1::SetSightRange(float r)
{
	sightRange = r;
}


void Enemy1::SetMoveSpeed(float r)
{
	moveSpeed = r;
}

void Enemy1::SetAttackCooldown(float r)
{
	attackCooldown = r;
}

void Enemy1::SpawnGeos()
{
	//for (int i = 0; i < 2; i++)
	//{
	//	GameplayStatics::CreateObject<Geo>(GetWorldPosition())->Init("1geo", 1);
	//}
}

void Enemy1::Die()
{
	Super::Die();

	ani->SetNode("die");
	rigid->SetGravityEnabled(true);
}

void Enemy1::CheckPlayerInRange() {
	if (player) {
		FVector2D enemyPos = GetWorldPosition();
		FVector2D playerPos = player->GetWorldPosition();
		float distance = FVector2D::Distance(enemyPos, playerPos);

		if (distance <= sightRange) {
			if (distance <= attackRange) {
				if (bChasing) {
					bChasing = false;
					ani->SetBool("chasing", false);
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
void Enemy1::ChasePlayer(float deltaTime) {
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
					rigid->SetVelocity({ direction.x * (chaseMaxBoundary.x - enemyPos.x) ,0});
				}
			}
			else {
			rigid->SetVelocity({direction.x * moveSpeed,0});
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

void Enemy1::AttackPlayer() {
	// ���Ź�������
	ani->SetBool("canAttack",true);

	// ����������
	EnemyAtkBox* attackBox = GameplayStatics::CreateObject<EnemyAtkBox>();
	attackBox->SetSize({27,66});
	attackBox->AttachTo(this);
	// ���ݵ��˳������ù�����λ��

	FVector2D enemyPos = GetWorldPosition();
	FVector2D playerPos = player->GetWorldPosition();
	FVector2D direction = (playerPos - enemyPos).GetSafeNormal();

	FVector2D attackBoxOffset = FVector2D(25, 0);
	attackBox->SetLocalPosition(attackBoxOffset);
	attackBox->Init(direction.x>0?AttackDirection::Right: AttackDirection::Left, 1); // ���蹥����Ϊ3

	// ���ù�����ȴʱ��
	currentCooldown = attackCooldown;
}

void Enemy1::SetChaseBoundary(FVector2D minBoundary, FVector2D maxBoundary)
{
	chaseMinBoundary = minBoundary;
	chaseMaxBoundary = maxBoundary;
}
#include "Enemy.h"
#include "Components/SpriteRenderer.h"
#include "Components/Collider.h"
#include "Components/RigidBody.h"
#include "DamageResponseComponent.h"
#include "PropertyComponent.h"
#include "Player.h"
#include "PlatForm.h"
#include "GameplayStatics.h"
#include "Effect.h"
#include "Components/ParticleSystem.h"
//#include "SilkParticle.h"
#include "GameModeHelper.h"
#include "AttackBox.h"



Enemy::Enemy()
{
	render = ConstructComponent<SpriteRenderer>();
	render->SetLayer(1);
	box = ConstructComponent<BoxCollider>();
	rigid = ConstructComponent<RigidBody>();
	ani = ConstructComponent<Animator>();
	ani->SetupAttachment(render);

	SetRootComponent(render);
	render_death = ConstructComponent<SpriteRenderer>();
	render_death->AttachTo(root);
	render_death->LoadSprite("death_light");
	render_death->SetLayer(-1);
	render_death->Deactivate();

	box->AttachTo(root);
	box->SetSize({ 15, 1000 });
	box->SetType(CollisionType::Enemy);
	box->SetCollisonMode(CollisionMode::Collision);
	rigid->SetAngularDrag(0.5f);
	rigid->SetRotatable(false);

	damageResponse = ConstructComponent<DamageResponseComponent>();
	property = ConstructComponent<PropertyComponent>();

	hurtTimer = 0.f;
}

void Enemy::BeginPlay()
{
	Super::BeginPlay();

	//box->OnComponentBeginOverlap.AddDynamic(this, &Enemy::OnOverlap);

	if (!player)
	{
		player = GameplayStatics::FindObjectOfClass<Player>();
	}
}

void Enemy::Update(float deltaTime)
{
	Super::Update(deltaTime);

	if (IsDead() && rigid->GetVelocity().Equals(FVector2D::ZeroVector))
	{
		rigid->SetRotatable(false);
	}

	hurtTimer -= deltaTime;

	if (!player)
	{
		player = GameplayStatics::FindObjectOfClass<Player>();
	}

	if (IsDead() && render_death->GetEnabled())
	{
		int trans = int(render_death->GetTransparency()) - int(deltaTime * 500);
		if (trans > 0) { render_death->SetTransparency(trans); render_death->SetLocalScale(GetLocalScale() * 0.98f); }
		else render_death->Deactivate();
	}
}

FDamageCauseInfo Enemy::TakeDamage(IDamagable* damageCauser, float baseValue, EDamageType damageType)
{
	if (hurtTimer > 0)
	{
		return {};
	}
	FDamageCauseInfo damageInfo = damageResponse->TakeDamage(damageCauser, baseValue, damageType);
	property->AddHealth(-baseValue);

	return damageInfo;
}

void Enemy::ExecuteDamageDealtEvent(FDamageCauseInfo extraInfo)
{
}

void Enemy::ExecuteDamageTakenEvent(FDamageCauseInfo extraInfo)
{
	if (!extraInfo.bIsValid)
	{
		return;
	}
	hurtTimer = 0.1f;
	Actor* causer = Cast<Actor>(extraInfo.damageCauser);
	CHECK_PTR(causer)
	AttackBox * atkbox = Cast<AttackBox>(causer);
		if (atkbox)
		{
			causer = box->GetOwner();
		}
	FVector2D normal = (GetWorldPosition() - causer->GetWorldPosition()).GetSafeNormal();
	float delta_x = causer->GetWorldPosition().x - GetWorldPosition().x;

	GameplayStatics::PlayCameraShake(4);
	render->Blink(0.3f, RGB(255, 110, 40));

	if (property->GetHealth() <= 0 && !IsDead())
	{
		Die();
	}
	else
	{
		
	}

	//Effect* effect = GameplayStatics::CreateObject<Effect>(GetWorldPosition());
	//if (effect)
	//{
	//	effect->SetLocalRotation(FMath::RandInt(-15, 15) + FVector2D::VectorToDegree(normal));
	//	effect->Init("effect_attack", -0.03f);
	//	effect->SetLocalScale(FVector2D{ delta_x < 0 ? 1.f : -1.f ,1.f }*FMath::RandReal(1, 1.5));
	//}
}

PropertyComponent* Enemy::GetProperty()
{
	return property;
}

void Enemy::OnOverlap(Collider* hitComp, Collider* otherComp, Actor* otherActor)
{
	//if (Player* player = Cast<Player>(otherActor))
	//{
	//	GameModeHelper::ApplyDamage(this, player, 1, EDamageType::Enemy);
	//}
}

void Enemy::Die()
{
	//SpawnGeos();

	bIsDead = true;
	render->SetLayer(-1);
	GameplayStatics::PlayCameraShake(8, 15);

	render_death->Activate();
	render_death->SetLocalPosition(GetWorldPosition());
	render_death->DetachFrom(root);
	render_death->SetOwner(nullptr);//开发者偷懒而使用的危险代码，请勿模仿

	box->OnComponentBeginOverlap.RemoveDynamic(this, &Enemy::OnOverlap);
	box->SetPhysicsMaterial(FPhysicsMaterial(0.6f, 0.6f));
	box->SetCollisionResponseToType(CollisionType::Dart, false);
	rigid->SetGravity(1960.f);

	//Effect* effect = GameplayStatics::CreateObject<Effect>(GetWorldPosition());
	//if (effect)effect->Init("effect_death");
}
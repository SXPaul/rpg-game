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

	idle_to_react.Init(idle, react);
	idle_to_react.AddCondition(AnimTransition::Bool{ "chasing",true });
	//turn_to_idle.Init(turn, idle);
	//turn_to_chase.Init(turn, chase);
	//turn_to_chase.AddCondition(AnimTransition::Bool{ "chasing",true });
	react_to_walk.Init(react, walk);
	walk_to_die.Init(walk, idle);
	walk_to_die.AddCondition(AnimTransition::Bool{ "chasing",false });

	ani->Insert("idle", idle);
	//ani->Insert("turn", turn);
	ani->Insert("react", react	);
	ani->Insert("walk", walk);
	ani->Insert("die", die);
	ani->SetNode("idle");

	ani->AddParamater("chasing", ParamType::Bool);
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
		//SilkParticle* silk = GameplayStatics::CreateObject<SilkParticle>();
		//silk->AttachTo(this);
		//silk->Init({}, true);
		rigid->AddImpulse({ 0,-500 });
		Die();
	}

	if (IsDead() || !player)return;

	if (FVector2D::Distance(player->GetWorldPosition(), GetWorldPosition()) < 400)
	{
		//if ((player->GetWorldPosition() - GetWorldPosition()).x * GetWorldScale().x < 0)
		//{
		//	SetLocalScale(FVector2D(-GetWorldScale().x, 1));
		//	ani->PlayMontage("turn");
		//}
		ani->SetBool("chasing", true);
		rigid->AddImpulse((player->GetWorldPosition() - GetWorldPosition()).GetSafeNormal() * deltaTime * 500.f);
		if (!bChasing)
		{
			//GameModeHelper::PlayFXSound("sound_fly_chase_" + std::to_string(FMath::RandInt(0, 1))); 
			bChasing = true;
		}
	}
	else
	{
		ani->SetBool("chasing", false); bChasing = false;
	}

}

void Enemy1::ExecuteDamageTakenEvent(FDamageCauseInfo extraInfo)
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
	if (property->GetHealth() <= 0)
	{
		rigid->SetAngularVelocity(200 * (delta_x > 0 ? 1.f : -1.f) * GetWorldScale().x);
	}
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
	//GameModeHelper::PlayFXSound("sound_fly_die");
	circle->SetRadius(20);
}

//void Enemy::OnOverlap(Collider* hitComp, Collider* otherComp, Actor* otherActor)
//{
//
//}
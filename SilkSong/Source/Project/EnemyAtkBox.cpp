#include "EnemyAtkBox.h"
#include "Components/Collider.h"
#include "GameplayStatics.h"
#include "Effect.h"
#include "Interactive.h"
#include "Player.h"
#include "GameModeHelper.h"


EnemyAtkBox::EnemyAtkBox()
{
	box = ConstructComponent<BoxCollider>();
	box->AttachTo(root);
	box->SetSize({ 220,150 });
	box->SetType(CollisionType::HurtBox);
	box->SetCollisonMode(CollisionMode::None);

	AttackTimerHandle.Bind(0.03f, [this]() {box->SetCollisonMode(CollisionMode::Trigger); }, false);
	DestroyTimerHandle.Bind(0.08f, [this]() {Destroy(); }, false);

	box->OnComponentBeginOverlap.AddDynamic(this, &EnemyAtkBox::OnOverlap);
	box->OnComponentEndOverlap.AddDynamic(this, &EnemyAtkBox::OnEndOverlap);
}

void EnemyAtkBox::Init(AttackDirection direction, int32 damage)
{
	this->direction = direction;
	if (direction == AttackDirection::Up)
	{
		box->SetSize({ 150, 220 });
		box->AddPosition({ 0, -70 });
	}
	else if (direction == AttackDirection::Down)
	{
		box->SetSize({ 150, 150 });
		box->AddPosition({ 0, 25 });
	}
	this->damage = damage;
}


void EnemyAtkBox::OnOverlap(Collider* hitComp, Collider* otherComp, Actor* otherActor)
{
	if (!GetOwner())return;
	FVector2D normal = (-GetOwner()->GetWorldPosition() + otherActor->GetWorldPosition()).GetSafeNormal();
	Player* player = GameplayStatics::FindObjectOfClass<Player>();
		GameModeHelper::ApplyDamage(this, player, this->damage, EDamageType::Player);

}

void EnemyAtkBox::OnEndOverlap(Collider* hitComp, Collider* otherComp, Actor* otherActor)
{
	if (hitComp->GetType() == CollisionType::Enemy || hitComp->GetType() == CollisionType::Dart)
	{
		box->SetCollisonMode(CollisionMode::None);
	}
}

void EnemyAtkBox::SetSize(FVector2D size) {
	box->SetSize(size);
}

void EnemyAtkBox::SetLocalPosition(FVector2D pos) {
	box->SetLocalPosition(pos);
}

float EnemyAtkBox::GetDamage()
{
	return damage;
}

#include "Player.h"
#include "Components/Collider.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody.h"
#include "Components/Camera.h"

Player::Player()
{
    render = GetComponentByClass<SpriteRenderer>();
    if (render) render->SetLayer(1);

    box = GetComponentByClass<BoxCollider>();
    if (box) {
        box->SetSize({ 30, 130 });
        box->SetLocalPosition({ -5, 10 });
        box->SetCollisonMode(CollisionMode::Collision);
        box->SetType(CollisionType::Player);
        box->SetPhysicsMaterial(FPhysicsMaterial(0.1f, 0));
    }

    rigid = GetComponentByClass<RigidBody>();
    if (rigid) {
        rigid->SetLinearDrag(0.07f);
        rigid->SetGravity(1960);
    }

    walkLock = 0;
}

void Player::Update(float deltaTime)
{
    Super::Update(deltaTime);
    // ��ѡ��������������һЩ�ٶ����ƻ򶯻���������
}

void Player::SetupInputComponent(InputComponent* inputComponent)
{
    inputComponent->SetMapping("WalkLeft", EKeyCode::VK_A);
    inputComponent->SetMapping("WalkRight", EKeyCode::VK_D);
    inputComponent->SetMapping("WalkLeftEnd", EKeyCode::VK_A);
    inputComponent->SetMapping("WalkRightEnd", EKeyCode::VK_D);

    inputComponent->BindAction("WalkLeft", EInputType::Holding, [this]() {
        walkLock = 1;
        AddInputX(-3.f, true);
        });
    inputComponent->BindAction("WalkLeftEnd", EInputType::Released, [this]() {
        if (walkLock == 1) walkLock = 0;
        });
    inputComponent->BindAction("WalkRight", EInputType::Holding, [this]() {
        walkLock = 2;
        AddInputX(3.f, true);
        });
    inputComponent->BindAction("WalkRightEnd", EInputType::Released, [this]() {
        if (walkLock == 2) walkLock = 0;
        });
}

FVector2D Player::GetCameraPos()
{
    if (camera)return camera->GetVirtualPosition();
    return FVector2D();
}
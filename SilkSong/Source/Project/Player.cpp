#include "Player.h"
#include "Components/Collider.h"
#include "Components/SpriteRenderer.h"
#include "Components/RigidBody.h"
#include "Components/Camera.h"
#include "PlayerAnimator.h"
#include <cstdlib>
Player::Player()
{
    render = GetComponentByClass<SpriteRenderer>();
    // 创建 PlayerAnimator 组件
    ani = ConstructComponent<PlayerAnimator>();
    //// 将 PlayerAnimator 与渲染器关联
    ani->SetupAttachment(render);
    if (render) render->SetLayer(1);

    box = GetComponentByClass<BoxCollider>();
    if (box) {
        box->SetSize({ 30, 70 });
        box->SetLocalPosition({ -15, 10 });
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

void Player::BeginPlay()
{
    Super::BeginPlay();
    if (ani) {
        ani->SetNode("idle");
    }
}

void Player::Update(float deltaTime)
{
    Super::Update(deltaTime);
    // 可选：可以在这里做一些速度限制或动画参数设置
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
#pragma once
#include "Objects/Character.h"
#include "Damagable.h"
#include "PropertyCarrier.h"
#include "GameUI.h"

enum class AttackDirection
{
    Left,
    Right,
    Up,
    Down,
};

class Player : public Character, public IDamagable, public IPropertyCarrier
{
    DEFINE_SUPER(Character)

public:
    Player();
    virtual void Update(float deltaTime) override;
    FVector2D GetCameraPos();
    virtual void BeginPlay()override;

    int32 GetHealth()const;
    void AddHealth(int32 delta);
    void DieStart();
    void DieEnd();

    virtual FDamageCauseInfo TakeDamage(IDamagable* damageCauser, float baseValue, EDamageType damageType) override;
    virtual void ExecuteDamageTakenEvent(FDamageCauseInfo extraInfo) override;

    virtual PropertyComponent* GetProperty() override;

    virtual void ExecuteDamageDealtEvent(FDamageCauseInfo extraInfo) override;

protected:
    virtual void SetupInputComponent(InputComponent* inputComponent) override;
    void StartCollision(Collider* hitComp, Collider* otherComp, Actor* otherActor, FVector2D normalImpulse, const FHitResult& hitResult);
    void StayCollision(Collider* hitComp, Collider* otherComp, Actor* otherActor, FVector2D normalImpulse, const FHitResult& hitResult);


private:
    class SpriteRenderer* render;
    class BoxCollider* box;
    class BoxCollider* hurtBox;
    class RigidBody* rigid;
    class Camera* camera;
    class PlayerAnimator* ani;
    class GameUI* ui;

    class DamageResponseComponent* damageResponse;
    class PlayerPropertyComponent* playerProperty;

    bool isonGround;
    bool isDashing; // 是否正在冲刺

    AttackDirection curDirection;
    AttackDirection lastDirection;

    Timer BlinkTimer;
    int blinkTimes;


    int32 walkLock = 0;
    int32 jumpLock = 0;
    float lastJumpTime = 0.0f; // 上次跳跃的时间戳
    float lastAttackTime = 0.0f; // 上次攻击的时间戳
    float lastDashTime = 0.0f;
};
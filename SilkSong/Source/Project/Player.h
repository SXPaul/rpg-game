#pragma once
#include "Objects/Character.h"

class Player : public Character
{
    DEFINE_SUPER(Character)

public:
    Player();
    virtual void Update(float deltaTime) override;
    FVector2D GetCameraPos();
    virtual void BeginPlay()override;

protected:
    virtual void SetupInputComponent(InputComponent* inputComponent) override;
    void StartCollision(Collider* hitComp, Collider* otherComp, Actor* otherActor, FVector2D normalImpulse, const FHitResult& hitResult);
    void StayCollision(Collider* hitComp, Collider* otherComp, Actor* otherActor, FVector2D normalImpulse, const FHitResult& hitResult);


private:
    class SpriteRenderer* render;
    class BoxCollider* box;
    class RigidBody* rigid;
    class Camera* camera;
    class PlayerAnimator* ani;

	bool isonGround;

    int32 walkLock = 0;
    int32 jumpLock = 0;
	float lastJumpTime = 0.0f; // 上次跳跃的时间戳
};
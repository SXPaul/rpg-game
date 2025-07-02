#pragma once
#include "Objects/Character.h"

class Player : public Character
{
    DEFINE_SUPER(Character);

public:
    Player();
    virtual void Update(float deltaTime) override;
    FVector2D GetCameraPos();
    virtual void BeginPlay()override;

protected:
    virtual void SetupInputComponent(InputComponent* inputComponent) override;

private:
    class SpriteRenderer* render;
    class BoxCollider* box;
    class RigidBody* rigid;
    class Camera* camera;
    class PlayerAnimator* ani;

    int32 walkLock;
};
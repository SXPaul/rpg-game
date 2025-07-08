// PlayerModel.h
#pragma once
#include "PlayerPropertyComponent.h"

class PlayerModel
{
private:
    PlayerPropertyComponent* propertyComponent;
    bool bGround;
    bool bEvading;
    bool bDashing;
    bool bFloating;
    bool bRushing;
    bool bRushFlag;
    bool bSitting;
    bool bWall;
    float lastJumpTime;
    float lastAttackTime;
    float lastEvadeTime;
    float lastDashTime;
    float lastFloatTime;
    float lastThrowTime;
    int32 attackFlag;
    int32 lookFlag;
    int32 jumpFlag;
    int32 walkLock;

public:
    PlayerModel()
    {
        propertyComponent = new PlayerPropertyComponent();
        bGround = false;
        bEvading = false;
        bDashing = false;
        bFloating = false;
        bRushing = false;
        bRushFlag = false;
        bSitting = false;
        bWall = false;
        lastJumpTime = 0.f;
        lastAttackTime = 0.f;
        lastEvadeTime = 0.f;
        lastDashTime = 0.f;
        lastFloatTime = 0.f;
        lastThrowTime = 0.f;
        attackFlag = 0;
        lookFlag = 0;
        jumpFlag = 1;
        walkLock = 0;
    }

    ~PlayerModel()
    {
        delete propertyComponent;
    }

    PlayerPropertyComponent* GetPropertyComponent() const
    {
        return propertyComponent;
    }

    // 其他属性的访问器和修改器
    bool IsGrounded() const { return bGround; }
    void SetGrounded(bool value) { bGround = value; }

    // 其他属性的访问器和修改器...
};
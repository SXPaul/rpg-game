// PlayerView.h
#pragma once
#include "Components/SpriteRenderer.h"
#include "PlayerAnimator.h"
//#include "GameUI.h"

class PlayerView
{
private:
    SpriteRenderer* render;
    SpriteRenderer* render_light;
    PlayerAnimator* ani;
    //GameUI* ui;

public:
    PlayerView(SpriteRenderer* r, SpriteRenderer* rl, PlayerAnimator* a, GameUI* u)
        : render(r), render_light(rl), ani(a), ui(u) {
    }

    void Update(float deltaTime)
    {
        // 更新动画参数
        ani->SetFloat("walkingSpeed", 0.f); // 这里需要根据实际情况更新
        ani->SetFloat("landingSpeed", -1.f);
        ani->SetFloat("fallingSpeed", 0.f);
        // 其他动画参数更新...
    }

    // 其他视图相关的方法
    void ShowDashEffect()
    {
        // 显示冲刺特效
    }

    void ShowCureEffect()
    {
        // 显示治疗特效
    }
};
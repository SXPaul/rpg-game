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
        // ���¶�������
        ani->SetFloat("walkingSpeed", 0.f); // ������Ҫ����ʵ���������
        ani->SetFloat("landingSpeed", -1.f);
        ani->SetFloat("fallingSpeed", 0.f);
        // ����������������...
    }

    // ������ͼ��صķ���
    void ShowDashEffect()
    {
        // ��ʾ�����Ч
    }

    void ShowCureEffect()
    {
        // ��ʾ������Ч
    }
};
// PlayerViewModel.h
#pragma once
#include "PlayerModel.h"
#include "PlayerView.h"

class PlayerViewModel
{
private:
    PlayerModel* model;
    PlayerView* view;

public:
    PlayerViewModel(PlayerModel* m, PlayerView* v)
        : model(m), view(v) {
    }

    void Update(float deltaTime)
    {
        // 更新模型状态
        // 根据模型状态更新视图
        if (model->IsGrounded())
        {
            // 处理玩家在地面上的视图逻辑
        }
        else
        {
            // 处理玩家在空中的视图逻辑
        }

        view->Update(deltaTime);
    }

    // 处理输入事件
    void OnWalkLeft()
    {
        // 更新模型状态
        // 根据模型状态更新视图
    }

    void OnWalkRight()
    {
        // 更新模型状态
        // 根据模型状态更新视图
    }

    // 其他输入事件处理方法...
};
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
        // ����ģ��״̬
        // ����ģ��״̬������ͼ
        if (model->IsGrounded())
        {
            // ��������ڵ����ϵ���ͼ�߼�
        }
        else
        {
            // ��������ڿ��е���ͼ�߼�
        }

        view->Update(deltaTime);
    }

    // ���������¼�
    void OnWalkLeft()
    {
        // ����ģ��״̬
        // ����ģ��״̬������ͼ
    }

    void OnWalkRight()
    {
        // ����ģ��״̬
        // ����ģ��״̬������ͼ
    }

    // ���������¼�������...
};
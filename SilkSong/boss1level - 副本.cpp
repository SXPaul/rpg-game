// Source/Project/NewLevel.cpp
#include "boss1level.h"
#include "GameplayStatics.h"
#include "PlatForm.h"
#include "Bg.h"
#include "GameModeHelper.h"
#include "LevelTransformer.h"

boss1level::boss1level()
{
    // ��ȡ��Ϸģʽʵ��
    GameMode* gameMode = GameModeHelper::GetInstance();
    gameMode->RefreshVolume();

    // ��֮ͣǰ�����֣������Ҫ��
    gameMode->GetAudioPlayer(0)->Pause("tearcity_i");
    gameMode->GetAudioPlayer(2)->Pause("tearcity_o");

    // �����¹ؿ��ı�������
    GameModeHelper::PlayBGMusic("new_level_music");

    // �����ؿ�ת�����������Ҫ�л��������ؿ���
    GameplayStatics::CreateObject<LevelTransformer>({ -1000, 875 })->Init("AnotherLevel", { 500, 900 }, FRect({ -100.f, 250.f }, { 100.f, 750.f }));

    // ������������
    Bg* bg0 = GameplayStatics::CreateObject<Bg>();
    bg0->Init("new_level_bg_0", -30);

    // ����ƽ̨����
    GameplayStatics::CreateObject<PlatForm>({ 0, 1075 })->Init("new_level_floor", { 2000, 200 }, {});

    // ������Ӹ���Ķ�������ߡ����˵�

    // �ؿ�ɾ��ʱ�Ĵ���
    OnLevelDelete.Add([this]() {
        GameMode* gameMode = GameModeHelper::GetInstance();
        gameMode->GetAudioPlayer(0)->Stop("new_level_music");
        });
}

void boss1level::Update(float deltaTime)
{
    Level::Update(deltaTime);

    // ���������ӹؿ��ĸ����߼����������Ҫ�����ǽ������������ջ����һЩ����Ч���ĸ����߼�
}
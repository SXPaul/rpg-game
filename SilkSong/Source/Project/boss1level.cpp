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
    //GameMode* gameMode = GameModeHelper::GetInstance();
    //gameMode->RefreshVolume();

    // ��֮ͣǰ�����֣������Ҫ��
    //gameMode->GetAudioPlayer(0)->Pause("tearcity_i");
    //gameMode->GetAudioPlayer(2)->Pause("tearcity_o");

    // �����¹ؿ��ı�������
    //GameModeHelper::PlayBGMusic("new_level_music");

    // �����ؿ�ת�����������Ҫ�л��������ؿ���
    //GameplayStatics::CreateObject<LevelTransformer>({ -1000, 875 })->Init("AnotherLevel", { 500, 900 }, FRect({ -100.f, 250.f }, { 100.f, 750.f }));

    // ������������
    Bg* bg0 = GameplayStatics::CreateObject<Bg>();
    bg0->Init("bg0", -30);
    Bg* bg1 = GameplayStatics::CreateObject<Bg>();
    bg1->Init("bg1", -15);
    // ����ƽ̨����
    //GameplayStatics::CreateObject<PlatForm>({ 0, 1075 })->Init("new_level_floor", { 2000, 200 }, {});
    PlatForm* platform1 = GameplayStatics::CreateObject<PlatForm>({ -300, 200 });
    platform1->Init("floor_tile_1", { 30, 30 }, { 0, 0 });
    PlatForm* platform2 = GameplayStatics::CreateObject<PlatForm>({ -235, 200 });
    platform2->Init("floor_tile_2", { 30, 30 }, { 0, 0 });
    platform2->SetLocalScale({ 100.0f / 30.0f, 1.0f });
    PlatForm* platform3 = GameplayStatics::CreateObject<PlatForm>({ -135, 200 });
    platform3->Init("floor_tile_3", { 30, 30 }, { 0, 0 });
    platform3->SetLocalScale({ 100.0f / 30.0f, 1.0f });
    PlatForm* platform4 = GameplayStatics::CreateObject<PlatForm>({ -70, 200 });
    platform4->Init("floor_tile_4", { 30, 30 }, { 0, 0 });
    PlatForm* platform5 = GameplayStatics::CreateObject<PlatForm>({ -5, 200 });
    platform5->Init("floor_tile_3", { 30, 30 }, { 0, 0 });
    platform5->SetLocalScale({ 100.0f / 30.0f, 1.0f });
    PlatForm* platform6 = GameplayStatics::CreateObject<PlatForm>({ 95, 200 });
    platform6->Init("floor_tile_3", { 30, 30 }, { 0, 0 });
    platform6->SetLocalScale({ 100.0f / 30.0f, 1.0f });
    PlatForm* platform7 = GameplayStatics::CreateObject<PlatForm>({195, 200 });
    platform7->Init("floor_tile_3", { 30, 30 }, { 0, 0 });
    platform7->SetLocalScale({ 100.0f / 30.0f, 1.0f });
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
// Source/Project/NewLevel.cpp
#include "boss1level.h"
#include "GameplayStatics.h"
#include "PlatForm.h"
#include "Bg.h"
#include "GameModeHelper.h"
#include "LevelTransformer.h"

boss1level::boss1level()
{
    // 获取游戏模式实例
    //GameMode* gameMode = GameModeHelper::GetInstance();
    //gameMode->RefreshVolume();

    // 暂停之前的音乐（如果需要）
    //gameMode->GetAudioPlayer(0)->Pause("tearcity_i");
    //gameMode->GetAudioPlayer(2)->Pause("tearcity_o");

    // 播放新关卡的背景音乐
    //GameModeHelper::PlayBGMusic("new_level_music");

    // 创建关卡转换器（如果需要切换到其他关卡）
    //GameplayStatics::CreateObject<LevelTransformer>({ -1000, 875 })->Init("AnotherLevel", { 500, 900 }, FRect({ -100.f, 250.f }, { 100.f, 750.f }));

    // 创建背景对象
    Bg* bg0 = GameplayStatics::CreateObject<Bg>();
    bg0->Init("bg0", -30);
    Bg* bg1 = GameplayStatics::CreateObject<Bg>();
    bg1->Init("bg1", -15);
    // 创建平台对象
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
    // 可以添加更多的对象，如道具、敌人等

    // 关卡删除时的处理
    OnLevelDelete.Add([this]() {
        GameMode* gameMode = GameModeHelper::GetInstance();
        gameMode->GetAudioPlayer(0)->Stop("new_level_music");
        });
}

void boss1level::Update(float deltaTime)
{
    Level::Update(deltaTime);

    // 这里可以添加关卡的更新逻辑，如果不需要与主角交互，可以留空或添加一些环境效果的更新逻辑
}
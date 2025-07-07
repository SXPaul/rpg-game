#include "StartLevel.h"
#include "GameplayStatics.h"
#include "PlatForm.h"
#include "Player.h"
#include "Bg.h"
#include "GameModeHelper.h"
#include "LevelTransformer.h"

StartLevel::StartLevel()
{
    SetDefaultController<Player>();

    // 创建背景对象
    Bg* bg0 = GameplayStatics::CreateObject<Bg>();
    bg0->Init("forest_1", -30);
    bg0->SetLocalScale(FVector2D(1.8f, 1.8f));
    Bg* bg1 = GameplayStatics::CreateObject<Bg>();
    bg1->Init("forest_2", -15);
    bg1->SetLocalScale(FVector2D(1.8f, 1.8f));
    Bg* bg2 = GameplayStatics::CreateObject<Bg>();
    bg2->Init("forest_3", -1);
    bg2->SetLocalScale(FVector2D(1.8f, 1.8f));

    GameplayStatics::CreateObject<PlatForm>({ -214.5, 0 })->Init("", { 31, 1000 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 1014.5, 0 })->Init("", { 31, 1000 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 400, 350 })->Init("", { 1600, 500 }, {});
    for (float x = -385; x < 1200.f; x += 30.f)
        for (float y = 115.0; y < 600.f; y += 30.f)
            GameplayStatics::CreateObject<PlatForm>({ x,y })->Init("brick_5", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 360, 40 })->Init("door_pro", { 80, 120 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 460, 40 })->Init("", { 120, 120 }, {});
    for (float x = 415; x < 520.f; x += 30.f)
        for (float y = -5.0; y < 100.f; y += 30.f)
            GameplayStatics::CreateObject<PlatForm>({ x,y })->Init("brick_7", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 420, -270 })->Init("", { 200, 500 }, {});
    for (float x = 335; x < 520.f; x += 30.f)
        for (float y = -505.0; y < -20.f; y += 30.f)
            GameplayStatics::CreateObject<PlatForm>({ x,y })->Init("brick_8", { 30, 30 }, {});
    GameplayStatics::CreateObject<LevelTransformer>({ 360,40 })->Init("LevelA", { 0,0 }, FRect({ 0.f,1110.f }, { 90.f,1400.f }));
    /* net */
    for (float x = -1000; x < 3000.f; x += 100.f)
        GameplayStatics::CreateObject<LevelTransformer>({ x,3000.0 })->Init("Boss", { 0,0 }, FRect({ 0.f,1110.f }, { 90.f,1400.f }));
    // 可以添加更多的对象，如道具、敌人等

    // 关卡删除时的处理
    OnLevelDelete.Add([this]() {
        GameMode* gameMode = GameModeHelper::GetInstance();
        //gameMode->GetAudioPlayer(0)->Stop("new_level_music");
        });
}

void StartLevel::Update(float deltaTime)
{
    Level::Update(deltaTime);

    // 这里可以添加关卡的更新逻辑，如果不需要与主角交互，可以留空或添加一些环境效果的更新逻辑
}
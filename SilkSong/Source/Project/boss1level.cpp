// Source/Project/NewLevel.cpp
#include "boss1level.h"
#include "GameplayStatics.h"
#include "PlatForm.h"
#include "Player.h"
#include "Bg.h"
#include "GameModeHelper.h"
#include "LevelTransformer.h"
#include "NightBorne.h"
#include "Boss1UI.h"
boss1level::boss1level()
{
    SetDefaultController<Player>();

    // 创建背景对象
    Bg* bg0 = GameplayStatics::CreateObject<Bg>();
    bg0->Init("bg0_pro", -30);
    bg0->SetLocalScale({ 1200.f / 950.f,800.f / 650.f });
    bg0->SetLocalPosition({ 400,0 });
    Bg* bg1 = GameplayStatics::CreateObject<Bg>();
    bg1->Init("bg1_pro", -15);
    bg1->SetLocalScale({ 1200.f / 950.f,800.f / 650.f });
    bg1->SetLocalPosition({ 400,0 });
    NightBorne* e;
    e = GameplayStatics::CreateObject<NightBorne>({ 400,0 });
    e->SetChaseBoundary({ -450,0 }, { 450,0 });
    GameplayStatics::CreateObject<PlatForm>({ -214.5, 0 })->Init("", { 31, 1000 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 1014.5, 0 })->Init("", { 31, 1000 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 400, 350 })->Init("", { 1600, 500 }, {});
    for (float x = -385; x < 1200.f; x += 30.f)
        for (float y = 115.0; y < 600.f; y += 30.f)
            GameplayStatics::CreateObject<PlatForm>({ x,y })->Init("brick_5", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -240, 40 })->Init("door_pro", { 80, 120 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -340, 40 })->Init("", { 120, 120 }, {});
    for (float x = -385; x < -280.f; x += 30.f)
        for (float y = -5.0; y < 100.f; y += 30.f)
            GameplayStatics::CreateObject<PlatForm>({ x,y })->Init("brick_7", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -300, -270 })->Init("", { 200, 500 }, {});
    for (float x = -385; x < -200.f; x += 30.f)
        for (float y = -505.0; y < -20.f; y += 30.f)
            GameplayStatics::CreateObject<PlatForm>({ x,y })->Init("brick_8", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 400, -600 })->Init("", { 1200, 400 }, {});
    for (float x = -185; x < 1600.f; x += 30.f)
        for (float y = -785.0; y < -400.f; y += 30.f)
            GameplayStatics::CreateObject<PlatForm>({ x,y })->Init("brick_10", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 1100, -210 })->Init("", { 200, 620 }, {});
    for (float x = 1015; x < 1200.f; x += 30.f)
        for (float y = -505.0; y < 100.f; y += 30.f)
            GameplayStatics::CreateObject<PlatForm>({ x,y })->Init("brick_11", { 30, 30 }, {});

    Draw_Platform(940, -210);
    Draw_Platform(820, -210);
    Draw_Platform(700, -210);
    Draw_Platform(580, -210);
    Draw_Platform(460, -210);
    Draw_Platform(340, -210);

    /* floor 2 */
    //GameplayStatics::CreateObject<PlatForm>({ 976.5, -346 })->Init("curtain_blue_right", { 47, 108 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -176.5, -346 })->Init("curtain_blue_left", { 47, 108 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 976.5, -146 })->Init("curtain_red_right", { 47, 108 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -176.5, -146 })->Init("curtain_red_left", { 47, 108 }, {});
    Bg* curtain;
    curtain = GameplayStatics::CreateObject<Bg>();
    curtain->Init("curtain_blue_left", 100);
    curtain->SetLocalPosition({ -165,-320 });
    curtain = GameplayStatics::CreateObject<Bg>();
    curtain->Init("curtain_blue_right", 100);
    curtain->SetLocalPosition({ 965,-320 });
    curtain = GameplayStatics::CreateObject<Bg>();
    curtain->Init("curtain_red_right", 100);
    curtain->SetLocalPosition({ 939,-60 });
    curtain = GameplayStatics::CreateObject<Bg>();
    curtain->Init("curtain_red_left", 100);
    curtain->SetLocalPosition({ -139,-60 });
    Bg* book;
    book = GameplayStatics::CreateObject<Bg>();
    book->Init("bookshelf_1", 1);
    book->SetLocalPosition({ 150,61.5 });
    book = GameplayStatics::CreateObject<Bg>();
    book->Init("flag_blue", 1);
    book->SetLocalPosition({ 340,-166.5 });
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

void boss1level::Update(float deltaTime)
{
    Level::Update(deltaTime);

    // 这里可以添加关卡的更新逻辑，如果不需要与主角交互，可以留空或添加一些环境效果的更新逻辑
}

void boss1level::Draw_Platform(float x, float y)
{
    /* platform 1, x: x-60 x+60, y: y-10 y+10  */
    GameplayStatics::CreateObject<PlatForm>({ x, y })->Init("", { 120, 20 }, {});
    GameplayStatics::CreateObject<PlatForm>({ x - 45, y + 7.5f })->Init("platform_shadow", { 30, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ x - 15, y + 7.5f })->Init("platform_shadow", { 30, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ x + 15, y + 7.5f })->Init("platform_shadow", { 30, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ x + 45, y + 7.5f })->Init("platform_shadow", { 30, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ x - 45, y - 2.5f })->Init("platform_1", { 30, 15 }, {});
    GameplayStatics::CreateObject<PlatForm>({ x - 15, y - 2.5f })->Init("platform_2", { 30, 15 }, {});
    GameplayStatics::CreateObject<PlatForm>({ x + 15, y - 2.5f })->Init("platform_3", { 30, 15 }, {});
    GameplayStatics::CreateObject<PlatForm>({ x + 45, y - 2.5f })->Init("platform_4", { 30, 15 }, {});
}
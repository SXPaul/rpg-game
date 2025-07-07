#include "LevelA.h"
#include "GameplayStatics.h"
#include "PlatForm.h"
#include "Player.h"
#include "Bg.h"
#include "GameModeHelper.h"
#include "LevelTransformer.h"
#include "Enemy1.h"
level_a::level_a()
{
    SetDefaultController<Player>();

    // background
    Bg* bg0 = GameplayStatics::CreateObject<Bg>();
    bg0->Init("bg0", -30);
    Bg* bg1 = GameplayStatics::CreateObject<Bg>();
    bg1->Init("bg1", -15);
    // enemy
    //Enemy1* e;
    //e=GameplayStatics::CreateObject<Enemy1>({ 400,0 });
    //e->SetChaseBoundary({ 240,0 }, {420,0});// range
    GameplayStatics::CreateObject<Enemy1>({ 400,100 })->SetChaseBoundary({ 240,0 }, { 420,0 });
    GameplayStatics::CreateObject<Enemy1>({ 700,100 })->SetChaseBoundary({ 600,0 }, { 800,0 });
    GameplayStatics::CreateObject<Enemy1>({ 570,550 })->SetChaseBoundary({ 540,0 }, { 600,0 });
    GameplayStatics::CreateObject<Enemy1>({ 435,370 })->SetChaseBoundary({ 400,0 }, { 470,0 });
    //GameplayStatics::CreateObject<Enemy1>({ 450,1050 })->SetChaseBoundary({ 225,1050 }, { 600,1050 });
    //GameplayStatics::CreateObject<Enemy1>({ 400,1140 })->SetChaseBoundary({ 225,0 }, { 600,0 });
    //GameplayStatics::CreateObject<Enemy1>({ 550,1140 })->SetChaseBoundary({ 225,0 }, { 600,0 });
    //GameplayStatics::CreateObject<PlatForm>({ 450.0, 1050.0 })->Init("", { 31, 31 }, {});
    // map
    PlatForm* temp;

    /* start point */
    GameplayStatics::CreateObject<PlatForm>({ -175, 85 })->Init("lion_10", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -145, 85 })->Init("lion_11", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -115, 85 })->Init("lion_12", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -175, 55 })->Init("lion_7", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -145, 55 })->Init("lion_8", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -115, 55 })->Init("lion_9", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -175, 25 })->Init("lion_4", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -145, 25 })->Init("lion_5", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -115, 25 })->Init("lion_6", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -175, -5 })->Init("lion_1", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -145, -5 })->Init("lion_2", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -115, -5 })->Init("lion_3", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -114.5, 40.0 })->Init("", { 31, 120 }, {});
    /* boundary */
    GameplayStatics::CreateObject<PlatForm>({ -235.0, 40.0 })->Init("", { 90, 120 }, {});
    for (float x = -265.0f; x < -190.0f; x += 30.0f)
        for (float y = -5.0f; y < 100.0f; y += 30.0f)
            GameplayStatics::CreateObject<PlatForm>({ x, y })->Init("brick_8", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -190.0, -270.0 })->Init("", { 180, 500 }, {});
    for (float x = -265.0f; x < -100.0f; x += 30.0f)
        for (float y = -505.0f; y < -20.0f; y += 30.0f)
            GameplayStatics::CreateObject<PlatForm>({ x, y })->Init("brick_7", { 30, 30 }, {});
    /* block 1 */
    GameplayStatics::CreateObject<PlatForm>({ -300, 200 })->Init("", { 1000, 200 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -785, 115 })->Init("floor_tile_1", { 30, 30 }, {});
    for (float x = -770.0f; x < 175.0f; x += 30.0f)
        GameplayStatics::CreateObject<PlatForm>({ x, 115.0f })->Init("floor_tile_2", { 30, 30 }, {});
    temp = GameplayStatics::CreateObject<PlatForm>({ 180.0, 115 });
    temp->Init("floor_tile_4", { 30, 30 }, {});
    temp->SetLocalScale({ 40.f / 30.0f, 1.f });
    for (float y = 145.0f; y < 310.0f; y += 30.0f)
    {
        for (float x = -785.0f; x < 175.0f; x += 30.0f)
            GameplayStatics::CreateObject<PlatForm>({ x, y })->Init("brick_1", { 30, 30 }, {});
        temp = GameplayStatics::CreateObject<PlatForm>({ 180.0, y });
        temp->Init("brick_1", { 30, 30 }, {});
    }
    /* block 1 end */
    /* block 2 */
    GameplayStatics::CreateObject<PlatForm>({ 300.0, 575.0 })->Init("", { 200, 850 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 395.5, 575 })->Init("", { 31, 850 }, {});
    for (float x = 215.0f; x < 380.0f; x += 30.0f)
        GameplayStatics::CreateObject<PlatForm>({ x, 165 })->Init("carpet_2", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 395, 165 })->Init("carpet_4", { 30, 30 }, {});
    for (float y = 195.0f; y < 1000.0f; y += 30.0f)
        for (float x = 215.0f; x < 400.0f; x += 30.0f)
            GameplayStatics::CreateObject<PlatForm>({ x, y })->Init("brick_2", { 30, 30 }, {});
    /* block 2 end */
    /* block 3 */
    GameplayStatics::CreateObject<PlatForm>({ 700.0, 675.0 })->Init("", { 200, 1050 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 614.5, 675.0 })->Init("", { 31, 1050 }, {});
    for (float y = 165.0f; y < 1200.0f; y += 30.0f)
        for (float x = 615.0f; x < 800.0f; x += 30.0f)
            GameplayStatics::CreateObject<PlatForm>({ x, y })->Init("brick_3", { 30, 30 }, {});
    /* block 3 end */
    /* block 4 */
    GameplayStatics::CreateObject<PlatForm>({ 570.0, 285.0 })->Init("", { 60, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 555, 285 })->Init("carpet_1", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 585, 285 })->Init("carpet_2", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 435.0, 405.0 })->Init("", { 70, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 425, 405 })->Init("carpet_3", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 455, 405 })->Init("carpet_4", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 570.0, 525.0 })->Init("", { 60, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 555, 525 })->Init("carpet_1", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 585, 525 })->Init("carpet_2", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 435.0, 645.0 })->Init("", { 70, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 425, 645 })->Init("carpet_3", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 455, 645 })->Init("carpet_4", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 570.0, 765.0 })->Init("", { 60, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 555, 765 })->Init("carpet_1", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 585, 765 })->Init("carpet_2", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 435.0, 885.0 })->Init("", { 70, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 425, 885 })->Init("carpet_3", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 455, 885 })->Init("carpet_4", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 570.0, 1005.0 })->Init("", { 60, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 555, 1005 })->Init("carpet_1", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 585, 1005 })->Init("carpet_2", { 30, 30 }, {});
    /* block 4 end */
    /* block 5 */
    GameplayStatics::CreateObject<PlatForm>({ 400.0, 1350.0 })->Init("", { 800, 300 }, {});
    for (float x = 15.0f; x < 800.0f; x += 30.0f)
        GameplayStatics::CreateObject<PlatForm>({ x, 1215.0f })->Init("floor_tile_3", { 30, 30 }, {});
    for (float y = 1245.0f; y < 1650.0f; y += 30.0f)
        for (float x = 15.0f; x < 800.0f; x += 30.0f)
            GameplayStatics::CreateObject<PlatForm>({ x, y })->Init("brick_5", { 30, 30 }, {});
    /* block 5 end */
    /* gate to Level B */
    GameplayStatics::CreateObject<LevelTransformer>({ 45.0, 1150.0 })->Init("LevelB", { -691,55 }, FRect({ 0.f,1110.f }, { 90.f,1200.f }));
    GameplayStatics::CreateObject<PlatForm>({ 10, 1185 })->Init("arch_6", { 20, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 80, 1185 })->Init("arch_7", { 20, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 10, 1155 })->Init("arch_4", { 20, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 80, 1155 })->Init("arch_5", { 20, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 15, 1125 })->Init("arch_1", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 45, 1120 })->Init("arch_2", { 30, 20 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 75, 1125 })->Init("arch_3", { 30, 30 }, {});
    temp = GameplayStatics::CreateObject<PlatForm>({ 45, 1170 });
    temp->Init("blank", { 20, 30 }, {});
    temp->SetLocalScale({ 50.f / 30.0f, 60.f / 30.0f });

    /* net */
    for (float x = -1000; x < 3000.f; x += 100.f)
        GameplayStatics::CreateObject<LevelTransformer>({ x,3000.0 })->Init("LevelAFail", { 0,0 }, FRect({ 0.f,1110.f }, { 90.f,1400.f }));

    // �ؿ�ɾ��ʱ�Ĵ���
    OnLevelDelete.Add([this]() {
        GameMode* gameMode = GameModeHelper::GetInstance();
        //gameMode->GetAudioPlayer(0)->Stop("new_level_music");
        });
}

void level_a::Update(float deltaTime)
{
    Level::Update(deltaTime);

    // ����������ӹؿ��ĸ����߼����������Ҫ�����ǽ������������ջ�����һЩ����Ч���ĸ����߼�
}
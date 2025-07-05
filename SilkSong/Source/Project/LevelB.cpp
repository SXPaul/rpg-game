#include "LevelB.h"
#include "GameplayStatics.h"
#include "PlatForm.h"
#include "Player.h"
#include "Bg.h"
#include "GameModeHelper.h"
#include "LevelTransformer.h"
level_b::level_b()
{
    // �������
    //if (!GameplayStatics::FindObjectOfClass<Player>())
    //{
        //auto player = GameplayStatics::CreateObject<Player>({ 0, 0 });
    //    // ����������������
    //    //player->GetComponentByClass<Camera>()->SetTarget(player);
    //}
    SetDefaultController<Player>();
    GameplayStatics::DontDestroyOnLoad(GameplayStatics::CreateObject<GameMode>());
    //Player* player = GameplayStatics::CreateObject<Player>();


    // ��ȡ��Ϸģʽʵ��
    //GameMode* gameMode = GameModeHelper::GetInstance();
    //gameMode->RefreshVolume();

    // ��֮ͣǰ�����֣������Ҫ��
    //gameMode->GetAudioPlayer(0)->Pause("tearcity_i");
    //gameMode->GetAudioPlayer(2)->Pause("tearcity_o");

    // �����¹ؿ��ı�������
    //GameModeHelper::PlayBGMusic("new_level_music");

    // background
    Bg* bg0 = GameplayStatics::CreateObject<Bg>();
    bg0->Init("bg0", -30);
    Bg* bg1 = GameplayStatics::CreateObject<Bg>();
    bg1->Init("bg1", -15);
    // map
    PlatForm* temp;
    /* start point */
    GameplayStatics::CreateObject<LevelTransformer>({ -145, 40 })->Init("LevelA", { 10,10 }, FRect({ -2200.f,-20.f }, { -120.f,100.f }));
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
    /* platform 1 */
    GameplayStatics::CreateObject<PlatForm>({ 315, -52.5 })->Init("platform_shadow", { 30, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 345, -52.5 })->Init("platform_shadow", { 30, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 375, -52.5 })->Init("platform_shadow", { 30, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 405, -52.5 })->Init("platform_shadow", { 30, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 315, -62.5 })->Init("platform_1", { 30, 15 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 345, -62.5 })->Init("platform_2", { 30, 15 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 375, -62.5 })->Init("platform_3", { 30, 15 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 405, -62.5 })->Init("platform_4", { 30, 15 }, {});
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
    /* block 2 */
    GameplayStatics::CreateObject<PlatForm>({ 300.0, 575.0 })->Init("", { 200, 850 }, {});
    for (float x = 215.0f; x < 380.0f; x += 30.0f)
        GameplayStatics::CreateObject<PlatForm>({ x, 165 })->Init("carpet_2", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 395, 165 })->Init("carpet_4", { 30, 30 }, {});
    for (float y = 195.0f; y < 1000.0f; y += 30.0f)
        for (float x = 215.0f; x < 400.0f; x += 30.0f)
            GameplayStatics::CreateObject<PlatForm>({ x, y })->Init("brick_2", { 30, 30 }, {});
    /* block 3 */
    GameplayStatics::CreateObject<PlatForm>({ 700.0, 675.0 })->Init("", { 200, 1050 }, {});
    for (float y = 165.0f; y < 1200.0f; y += 30.0f)
        for (float x = 615.0f; x < 800.0f; x += 30.0f)
            GameplayStatics::CreateObject<PlatForm>({ x, y })->Init("brick_3", { 30, 30 }, {});
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
    /* block 5 */
    GameplayStatics::CreateObject<PlatForm>({ 400.0, 1350.0 })->Init("", { 800, 300 }, {});
    for (float x = 15.0f; x < 800.0f; x += 30.0f)
        GameplayStatics::CreateObject<PlatForm>({ x, 1215.0f })->Init("floor_tile_3", { 30, 30 }, {});
    for (float y = 1245.0f; y < 1650.0f; y += 30.0f)
        for (float x = 15.0f; x < 800.0f; x += 30.0f)
            GameplayStatics::CreateObject<PlatForm>({ x, y })->Init("brick_5", { 30, 30 }, {});
    /* block 5 end */
    ///* gate to Level B */
    //GameplayStatics::CreateObject<LevelTransformer>({ 45.0, 1150.0 })->Init("LevelB", { -691,55 }, FRect({ 0.f,1110.f }, { 90.f,1200.f }));
    //GameplayStatics::CreateObject<PlatForm>({ 10, 1185 })->Init("arch_6", { 20, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 80, 1185 })->Init("arch_7", { 20, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 10, 1155 })->Init("arch_4", { 20, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 80, 1155 })->Init("arch_5", { 20, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 15, 1125 })->Init("arch_1", { 30, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 45, 1120 })->Init("arch_2", { 30, 20 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 75, 1125 })->Init("arch_3", { 30, 30 }, {});
    /* ==========coordinate========== */
    //GameplayStatics::CreateObject<PlatForm>({ 0,0 })->Init("", { 12000, 0 }, {}); // x
    //GameplayStatics::CreateObject<PlatForm>({ 100,0 })->Init("", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -100,0 })->Init("", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 200,0 })->Init("", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -200,0 })->Init("", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 300,0 })->Init("", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -300,0 })->Init("", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 400,0 })->Init("", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -400,0 })->Init("", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 500,0 })->Init("", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -500,0 })->Init("", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 600,0 })->Init("", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -600,0 })->Init("", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 0,0 })->Init("", { 0, 8000 }, {}); // y
    //GameplayStatics::CreateObject<PlatForm>({ 0,100 })->Init("", { 5, 0 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 0, -100 })->Init("", { 5, 0 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 0, 200 })->Init("", { 5, 0 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 0, -200 })->Init("", { 5, 0 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 0, 300 })->Init("", { 5, 0 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 0, -300 })->Init("", { 5, 0 }, {});
    /* =========================================================================== */
    // �ؿ�ɾ��ʱ�Ĵ���
    OnLevelDelete.Add([this]() {
        GameMode* gameMode = GameModeHelper::GetInstance();
        gameMode->GetAudioPlayer(0)->Stop("new_level_music");
        });
}

void level_b::Update(float deltaTime)
{
    Level::Update(deltaTime);

    // ����������ӹؿ��ĸ����߼����������Ҫ�����ǽ������������ջ�����һЩ����Ч���ĸ����߼�
}
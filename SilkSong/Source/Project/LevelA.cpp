#include "LevelA.h"
#include "GameplayStatics.h"
#include "PlatForm.h"
#include "Player.h"
#include "Bg.h"
#include "GameModeHelper.h"
#include "LevelTransformer.h"
level_a::level_a()
{
    // �������
    //if (!GameplayStatics::FindObjectOfClass<Player>())
    //{
    //    auto player = GameplayStatics::CreateObject<Player>({ 0, 0 });
    //    // ����������������
    //    //player->GetComponentByClass<Camera>()->SetTarget(player);
    //}
    SetDefaultController<Player>();
    GameplayStatics::DontDestroyOnLoad(GameplayStatics::CreateObject<GameMode>());
    //Player* player = GameplayStatics::CreateObject<Player>();
    //player->SetLocalPosition({ -0, -1000 });


    // ��ȡ��Ϸģʽʵ��
    GameMode* gameMode = GameModeHelper::GetInstance();
    //gameMode->RefreshVolume();

    // ��֮ͣǰ�����֣������Ҫ��
    //gameMode->GetAudioPlayer(0)->Pause("tearcity_i");
    //gameMode->GetAudioPlayer(2)->Pause("tearcity_o");

    // �����¹ؿ��ı�������
    //GameModeHelper::PlayBGMusic("new_level_music");

    // ������������
    Bg* bg0 = GameplayStatics::CreateObject<Bg>();
    bg0->Init("bg0", -30);
    Bg* bg1 = GameplayStatics::CreateObject<Bg>();
    bg1->Init("bg1", -15);
    // ����ƽ̨����
    PlatForm* temp;
    //temp = GameplayStatics::CreateObject<PlatForm>({ -750.0, 50.0 });
    //temp->Init("lion_column_8", { 30, 30 }, {});
    //temp->SetLocalScale({ 100.f / 30.0f, 100.f/30.0f });
    //temp = GameplayStatics::CreateObject<PlatForm>({ -300, 200 });
    //temp->Init("floor_tile_3", { 30, 30 }, {});
    //temp->SetLocalScale({ 1000.f / 30.0f, 200.f/30.0f });
    //temp = GameplayStatics::CreateObject<PlatForm>({ 300.0, 575.0 });
    //temp->Init("floor_tile_3", { 30, 30 }, {});
    //temp->SetLocalScale({ 200.f / 30.0f, 850.f/30.0f });
    //temp = GameplayStatics::CreateObject<PlatForm>({ 700.0, 675.0 });
    //temp->Init("floor_tile_3", { 30, 30 }, {});
    //temp->SetLocalScale({ 200.f / 30.0f, 1050.f/30.0f });
    //temp = GameplayStatics::CreateObject<PlatForm>({ 565.0, 285.0 });
    //temp->Init("floor_tile_3", { 30, 30 }, {});
    //temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    //temp = GameplayStatics::CreateObject<PlatForm>({ 435.0, 405.0 });
    //temp->Init("floor_tile_3", { 30, 30 }, {});
    //temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    //temp = GameplayStatics::CreateObject<PlatForm>({ 565.0, 525.0 });
    //temp->Init("floor_tile_3", { 30, 30 }, {});
    //temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    //temp = GameplayStatics::CreateObject<PlatForm>({ 435.0, 645.0 });
    //temp->Init("floor_tile_3", { 30, 30 }, {});
    //temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    //temp = GameplayStatics::CreateObject<PlatForm>({ 565.0, 765.0 });
    //temp->Init("floor_tile_3", { 30, 30 }, {});
    //temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    //temp = GameplayStatics::CreateObject<PlatForm>({ 435.0, 885.0 });
    //temp->Init("floor_tile_3", { 30, 30 }, {});
    //temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    //temp = GameplayStatics::CreateObject<PlatForm>({ 565.0, 1005.0 });
    //temp->Init("floor_tile_3", { 30, 30 }, {});
    //temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    //temp = GameplayStatics::CreateObject<PlatForm>({ 300.0, 1350.0 });
    //temp->Init("floor_tile_3", { 30, 30 }, {});
    //temp->SetLocalScale({ 600.f / 30.0f, 300.f/30.0f });
    //temp = GameplayStatics::CreateObject<PlatForm>({ 50.0, 1150.0 });
    //temp->Init("lion_column_8", { 30, 30 }, {});
    //temp->SetLocalScale({ 100.f / 30.0f, 100.f / 30.0f });
    GameplayStatics::CreateObject<PlatForm>({ -750.0, 50.0 })->Init("new_level_floor", { 100, 100 }, {});
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
    GameplayStatics::CreateObject<PlatForm>({ 300.0, 575.0 })->Init("new_level_floor", { 200, 850 }, {});
    for (float x = 215.0f; x < 380.0f; x += 30.0f)
        GameplayStatics::CreateObject<PlatForm>({ x, 165 })->Init("carpet_2", { 30, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 395, 165 })->Init("carpet_4", { 30, 30 }, {});
    for (float y = 195.0f; y < 1000.0f; y += 30.0f)
        for (float x = 215.0f; x < 400.0f; x += 30.0f)
            GameplayStatics::CreateObject<PlatForm>({ x, y })->Init("brick_2", { 30, 30 }, {});
    /* block 2 end */
    /* block 3 */
    GameplayStatics::CreateObject<PlatForm>({ 700.0, 675.0 })->Init("new_level_floor", { 200, 1050 }, {});
    for (float y = 165.0f; y < 1200.0f; y += 30.0f)
        for (float x = 615.0f; x < 800.0f; x += 30.0f)
            GameplayStatics::CreateObject<PlatForm>({ x, y })->Init("brick_3", { 30, 30 }, {});
    /* block 3 end */
    GameplayStatics::CreateObject<PlatForm>({ 565.0, 285.0 })->Init("new_level_floor", { 70, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 435.0, 405.0 })->Init("new_level_floor", { 70, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 565.0, 525.0 })->Init("new_level_floor", { 70, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 435.0, 645.0 })->Init("new_level_floor", { 70, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 565.0, 765.0 })->Init("new_level_floor", { 70, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 435.0, 885.0 })->Init("new_level_floor", { 70, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 565.0, 1005.0 })->Init("new_level_floor", { 70, 30 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 300.0, 1350.0 })->Init("new_level_floor", { 600, 300 }, {});
    GameplayStatics::CreateObject<LevelTransformer>({ 50.0, 1150.0 })->Init("LevelB", { -691,55 }, FRect({ 0.f,1100.f }, { 100.f,1200.f }));
    /* ==========coordinate========== */
    GameplayStatics::CreateObject<PlatForm>({ 0,0 })->Init("aaa", { 12000, 0 }, {}); // x
    GameplayStatics::CreateObject<PlatForm>({ 100,0 })->Init("aaa", { 0, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -100,0 })->Init("aaa", { 0, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 200,0 })->Init("aaa", { 0, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -200,0 })->Init("aaa", { 0, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 300,0 })->Init("aaa", { 0, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -300,0 })->Init("aaa", { 0, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 400,0 })->Init("aaa", { 0, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -400,0 })->Init("aaa", { 0, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 500,0 })->Init("aaa", { 0, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -500,0 })->Init("aaa", { 0, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 600,0 })->Init("aaa", { 0, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ -600,0 })->Init("aaa", { 0, 5 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 0,0 })->Init("aaa", { 0, 8000 }, {}); // y
    GameplayStatics::CreateObject<PlatForm>({ 0,100 })->Init("aaa", { 5, 0 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 0, -100 })->Init("aaa", { 5, 0 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 0, 200 })->Init("aaa", { 5, 0 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 0, -200 })->Init("aaa", { 5, 0 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 0, 300 })->Init("aaa", { 5, 0 }, {});
    GameplayStatics::CreateObject<PlatForm>({ 0, -300 })->Init("aaa", { 5, 0 }, {});
    /* =========================================================================== */
    // item and enemy
    //GameplayStatics::CreateObject<Bug>({ 1100,890 }, 0.f, { -1.f,1.f });
    //GameplayStatics::CreateObject<Bug>({ 650,300 });
    //GameplayStatics::CreateObject<Bug>({ -500,890 });

    //GameplayStatics::CreateObject<Fly>({ 0,800 });
    //GameplayStatics::CreateObject<Fly>({ 450,500 }, 0.f, { -1.f,1.f });
    // �ؿ�ɾ��ʱ�Ĵ���
    OnLevelDelete.Add([this]() {
        GameMode* gameMode = GameModeHelper::GetInstance();
        gameMode->GetAudioPlayer(0)->Stop("new_level_music");
        });
}

void level_a::Update(float deltaTime)
{
    Level::Update(deltaTime);

    // ����������ӹؿ��ĸ����߼����������Ҫ�����ǽ������������ջ�����һЩ����Ч���ĸ����߼�
}
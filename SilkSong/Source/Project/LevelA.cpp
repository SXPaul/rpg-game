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
    //Player* player = GameplayStatics::CreateObject<Player>();
    //player->SetLocalPosition({ -0, -1000 });


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
    PlatForm* temp;
    temp = GameplayStatics::CreateObject<PlatForm>({ -750.0, 50.0 });
    temp->Init("lion_column_8", { 30, 30 }, {});
    temp->SetLocalScale({ 100.f / 30.0f, 100.f/30.0f });
    temp = GameplayStatics::CreateObject<PlatForm>({ -300, 200 });
    temp->Init("floor_tile_3", { 30, 30 }, {});
    temp->SetLocalScale({ 1000.f / 30.0f, 200.f/30.0f });
    temp = GameplayStatics::CreateObject<PlatForm>({ 300.0, 575.0 });
    temp->Init("floor_tile_3", { 30, 30 }, {});
    temp->SetLocalScale({ 200.f / 30.0f, 850.f/30.0f });
    temp = GameplayStatics::CreateObject<PlatForm>({ 700.0, 675.0 });
    temp->Init("floor_tile_3", { 30, 30 }, {});
    temp->SetLocalScale({ 200.f / 30.0f, 1050.f/30.0f });
    temp = GameplayStatics::CreateObject<PlatForm>({ 565.0, 285.0 });
    temp->Init("floor_tile_3", { 30, 30 }, {});
    temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    temp = GameplayStatics::CreateObject<PlatForm>({ 435.0, 405.0 });
    temp->Init("floor_tile_3", { 30, 30 }, {});
    temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    temp = GameplayStatics::CreateObject<PlatForm>({ 565.0, 525.0 });
    temp->Init("floor_tile_3", { 30, 30 }, {});
    temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    temp = GameplayStatics::CreateObject<PlatForm>({ 435.0, 645.0 });
    temp->Init("floor_tile_3", { 30, 30 }, {});
    temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    temp = GameplayStatics::CreateObject<PlatForm>({ 565.0, 765.0 });
    temp->Init("floor_tile_3", { 30, 30 }, {});
    temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    temp = GameplayStatics::CreateObject<PlatForm>({ 435.0, 885.0 });
    temp->Init("floor_tile_3", { 30, 30 }, {});
    temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    temp = GameplayStatics::CreateObject<PlatForm>({ 565.0, 1005.0 });
    temp->Init("floor_tile_3", { 30, 30 }, {});
    temp->SetLocalScale({ 70.f / 30.0f, 30.f/30.0f });
    temp = GameplayStatics::CreateObject<PlatForm>({ 300.0, 1350.0 });
    temp->Init("floor_tile_3", { 30, 30 }, {});
    temp->SetLocalScale({ 600.f / 30.0f, 300.f/30.0f });
    temp = GameplayStatics::CreateObject<PlatForm>({ 50.0, 1150.0 });
    temp->Init("lion_column_8", { 30, 30 }, {});
    temp->SetLocalScale({ 100.f / 30.0f, 100.f / 30.0f });
    //GameplayStatics::CreateObject<PlatForm>({ -450.0, 50.0 })->Init("floor_tile_3", { 100, 100 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -300, 200 })->Init("floor_tile_3", { 1000, 200 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 300.0, 575.0 })->Init("floor_tile_3", { 200, 850 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 700.0, 675.0 })->Init("floor_tile_3", { 200, 1050 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 565.0, 285.0 })->Init("floor_tile_3", { 70, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 435.0, 405.0 })->Init("floor_tile_3", { 70, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 565.0, 525.0 })->Init("floor_tile_3", { 70, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 435.0, 645.0 })->Init("floor_tile_3", { 70, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 565.0, 765.0 })->Init("floor_tile_3", { 70, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 435.0, 885.0 })->Init("floor_tile_3", { 70, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 565.0, 1005.0 })->Init("floor_tile_3", { 70, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 300.0, 1350.0 })->Init("floor_tile_3", { 600, 300 }, {});
    // GameplayStatics::CreateObject<PlatForm>({ 0, 300 })->Init("floor_tile_3", { 200, 200 }, {});
    // GameplayStatics::CreateObject<PlatForm>({ 175, 225 })->Init("floor_tile_3", { 150, 150 }, {});
    // GameplayStatics::CreateObject<PlatForm>({ 425.0, 65.0 })->Init("floor_tile_3", { 350, 470 }, {});
    // GameplayStatics::CreateObject<PlatForm>({ 0, 1075 })->Init("floor_tile_3", { 2000, 200 }, {});
    /* ==========coordinate========== */
    //GameplayStatics::CreateObject<PlatForm>({ 0,0 })->Init("aaa", { 12000, 0 }, {}); // x
    //GameplayStatics::CreateObject<PlatForm>({ 100,0 })->Init("aaa", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -100,0 })->Init("aaa", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 200,0 })->Init("aaa", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -200,0 })->Init("aaa", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 300,0 })->Init("aaa", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -300,0 })->Init("aaa", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 400,0 })->Init("aaa", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -400,0 })->Init("aaa", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 500,0 })->Init("aaa", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -500,0 })->Init("aaa", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 600,0 })->Init("aaa", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ -600,0 })->Init("aaa", { 0, 5 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 0,0 })->Init("aaa", { 0, 8000 }, {}); // y
    //GameplayStatics::CreateObject<PlatForm>({ 0,100 })->Init("aaa", { 5, 0 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 0, -100 })->Init("aaa", { 5, 0 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 0, 200 })->Init("aaa", { 5, 0 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 0, -200 })->Init("aaa", { 5, 0 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 0, 300 })->Init("aaa", { 5, 0 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 0, -300 })->Init("aaa", { 5, 0 }, {});
    /* =========================================================================== */
    // �������Ӹ���Ķ�������ߡ����˵�
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
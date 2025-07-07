#include "LevelB.h"
#include "GameplayStatics.h"
#include "PlatForm.h"
#include "Player.h"
#include "Bg.h"
#include "GameModeHelper.h"
#include "LevelTransformer.h"
#include "UI/UserInterface.h"
level_b::level_b()
{
    //Image* Title;
    //Title = 
    //Title = AddWidget<Image>();
    //Title->AttachTo(rootCanvas);
    //Title->SetLayoutPattern(LayoutPattern::Center);
    //Title->SetRelativePosition(FVector2D(0, -175));
    //Title->SetSize(FVector2D(800, 150));
    //Title->LoadSprite("carpet_1");
    //Title->SetLayer(0);
    // �������
    //if (!GameplayStatics::FindObjectOfClass<Player>())
    //{
        //auto player = GameplayStatics::CreateObject<Player>({ 0, 0 });
    //    // ����������������
    //    //player->GetComponentByClass<Camera>()->SetTarget(player);
    //}
    SetDefaultController<Player>();
    GameplayStatics::DontDestroyOnLoad(GameplayStatics::CreateObject<GameMode>());
    //FVector2D  a = GetPosition();
    //std::string str = a.ToString();

    // 输出到终端
    //std::cout << "FVector2D a: " << str << std::endl;

    // ��ȡ��Ϸģʽʵ��
    //GameMode* gameMode = GameModeHelper::GetInstance();
    //gameMode->RefreshVolume();

    // ��֮ͣǰ�����֣������Ҫ��
    //gameMode->GetAudioPlayer(0)->Pause("tearcity_i");
    //gameMode->GetAudioPlayer(2)->Pause("tearcity_o");

    // �����¹ؿ��ı�������
    //GameModeHelper::PlayBGMusic("new_level_music");

    //MenuUI* menuUI = GameplayStatics::CreateUI<MenuUI>();
    //if (menuUI) {
    //    menuUI->AddToViewport();
    //}
    // background
    GameplayStatics::CreateObject<Bg>()->Init("forest_1_max", -30);
    GameplayStatics::CreateObject<Bg>()->Init("forest_2_max", -15);
    GameplayStatics::CreateObject<Bg>()->Init("forest_3_max", -1);
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
    /* platform 1, x: 300 420, y:-50 -70  */ 
    Draw_Platform(360, -60);
    /* platform 2, x: 450 570, y:-150 -170  */
    Draw_Platform(510, -160);
    /* platform 3, x: 850 570, y:-150 -170  */
    Draw_Platform(910, -160);
    /* platform 4, x: 600 720, y : -150 - 170 */
    Draw_Platform(660, 80);
    /* platform 5 */
    Draw_Platform(460, 280);
    /* 6 */
    Draw_Platform(710, -360);
    /* 7 */
    Draw_Platform(900, -500);
    Draw_Platform(710, -700);
    GameplayStatics::CreateObject<PlatForm>({ 710, -740 })->Init("door", { 40, 60 }, {});
    GameplayStatics::CreateObject<LevelTransformer>({ 710,-740 })->Init("Boss", { 0,0 }, FRect({ 10000.f,1110.f }, { 9000.f,1400.f }));
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
    ///* gate to Level B */
    //GameplayStatics::CreateObject<LevelTransformer>({ 45.0, 1150.0 })->Init("LevelB", { -691,55 }, FRect({ 0.f,1110.f }, { 90.f,1200.f }));
    //GameplayStatics::CreateObject<PlatForm>({ 10, 1185 })->Init("arch_6", { 20, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 80, 1185 })->Init("arch_7", { 20, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 10, 1155 })->Init("arch_4", { 20, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 80, 1155 })->Init("arch_5", { 20, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 15, 1125 })->Init("arch_1", { 30, 30 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 45, 1120 })->Init("arch_2", { 30, 20 }, {});
    //GameplayStatics::CreateObject<PlatForm>({ 75, 1125 })->Init("arch_3", { 30, 30 }, {});
    /* net */
    for (float x = -1000; x < 3000.f; x += 100.f)
        GameplayStatics::CreateObject<LevelTransformer>({ x,3000.0 })->Init("Menu", { 0,0 }, FRect({ 0.f,1110.f }, { 90.f,1400.f }));
    // �ؿ�ɾ��ʱ�Ĵ���
    OnLevelDelete.Add([this]() {
        GameMode* gameMode = GameModeHelper::GetInstance();
        //gameMode->GetAudioPlayer(0)->Stop("new_level_music");
        });
}

void level_b::Update(float deltaTime)
{
    Level::Update(deltaTime);
    // ����������ӹؿ��ĸ����߼����������Ҫ�����ǽ������������ջ�����һЩ����Ч���ĸ����߼�
}

void level_b::Draw_Platform(float x, float y)
{
    /* platform 1, x: x-60 x+60, y: y-10 y+10  */
    GameplayStatics::CreateObject<PlatForm>({ 360, -60 })->Init("", { 120, 20 }, {});
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
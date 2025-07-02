#include "FirstLevel.h"
#include "Player.h"
#include "GameplayStatics.h"
#include "Objects/Actor.h"
#include "PlatForm.h"
#include "Bg.h"
#include "GameModeHelper.h"
#include "LevelTransformer.h"

FirstLevel::FirstLevel()
{
    // 可选：设置关卡名等
}

void FirstLevel::BeginPlay()
{
    Super::BeginPlay();

    // 创建玩家
    Player* player = GameplayStatics::CreateObject<Player>();
    player->SetLocalPosition({ -0, -1000 });
    
    printf("Player world pos: %f, %f\n", player->GetWorldPosition().x, player->GetWorldPosition().y);

    // 创建平台

    GameplayStatics::CreateObject<PlatForm>({ -275, 200 })->Init("", { 900, 400 }, {});


    // 创建背景对象
    Bg* bg0 = GameplayStatics::CreateObject<Bg>();
    bg0->Init("bg0", -30);
    Bg* bg1 = GameplayStatics::CreateObject<Bg>();
    bg1->Init("bg1", -15);
    // 创建平台对象
    //GameplayStatics::CreateObject<PlatForm>({ 0, 1075 })->Init("new_level_floor", { 2000, 200 }, {});

    // 可以添加更多的对象，如道具、敌人等

    // 关卡删除时的处理
    OnLevelDelete.Add([this]() {
        GameMode* gameMode = GameModeHelper::GetInstance();
        gameMode->GetAudioPlayer(0)->Stop("new_level_music");
        });


    // 可选：设置平台为静态/不可移动
}
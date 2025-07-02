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
    // ��ѡ�����ùؿ�����
}

void FirstLevel::BeginPlay()
{
    Super::BeginPlay();

    // �������
    Player* player = GameplayStatics::CreateObject<Player>();
    player->SetLocalPosition({ -0, -1000 });
    
    printf("Player world pos: %f, %f\n", player->GetWorldPosition().x, player->GetWorldPosition().y);

    // ����ƽ̨

    GameplayStatics::CreateObject<PlatForm>({ -275, 200 })->Init("", { 900, 400 }, {});


    // ������������
    Bg* bg0 = GameplayStatics::CreateObject<Bg>();
    bg0->Init("bg0", -30);
    Bg* bg1 = GameplayStatics::CreateObject<Bg>();
    bg1->Init("bg1", -15);
    // ����ƽ̨����
    //GameplayStatics::CreateObject<PlatForm>({ 0, 1075 })->Init("new_level_floor", { 2000, 200 }, {});

    // ������Ӹ���Ķ�������ߡ����˵�

    // �ؿ�ɾ��ʱ�Ĵ���
    OnLevelDelete.Add([this]() {
        GameMode* gameMode = GameModeHelper::GetInstance();
        gameMode->GetAudioPlayer(0)->Stop("new_level_music");
        });


    // ��ѡ������ƽ̨Ϊ��̬/�����ƶ�
}
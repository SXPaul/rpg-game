#include "LevelBFail.h"
#include "GameplayStatics.h"
#include "LevelBFailController.h"
#include "Bg.h"

level_b_fail::level_b_fail()
{
    SetDefaultController<LevelBFailController>();
    Bg* bg0 = GameplayStatics::CreateObject<Bg>();
    bg0->Init("forest_1", -30);
    Bg* bg1 = GameplayStatics::CreateObject<Bg>();
    bg1->Init("forest_2", -15);
    Bg* bg2 = GameplayStatics::CreateObject<Bg>();
    bg2->Init("forest_3", -1);
}
#include "MenuLevel.h"
#include "GameplayStatics.h"
#include "MenuController.h"
#include "Bg.h"

MenuLevel::MenuLevel()
{
    //SetDefaultController<Player>();
	SetDefaultController<MenuController>();
    Bg* bg0 = GameplayStatics::CreateObject<Bg>();
    bg0->Init("forest_1", -30);
    Bg* bg1 = GameplayStatics::CreateObject<Bg>();
    bg1->Init("forest_2", -15);
    Bg* bg2 = GameplayStatics::CreateObject<Bg>();
    bg2->Init("forest_3", -1);
}
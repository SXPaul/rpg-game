#include "GameUI.h"
#include "Player.h"
#include "GameplayStatics.h"
#

GameUI::GameUI()
{
	Bar = AddWidget<Image>();
	Bar->AttachTo(rootCanvas);
	//Bar->SetLayoutPattern(LayoutPattern::Center);
	Bar->SetRelativePosition(FVector2D(125, 40));
	Bar->LoadSprite("bar");
	Bar->SetLayer(24);

	Bar_Background = AddWidget<Image>();
	Bar_Background->AttachTo(rootCanvas);
	Bar_Background->SetRelativePosition(FVector2D(125, 40));
	Bar_Background->LoadSprite("bar_background");
	Bar_Background->SetLayer(24);

	Health_Bar = AddWidget<Image>();
	Health_Bar->AttachTo(rootCanvas);
	Health_Bar->SetRelativePosition(FVector2D(125, 40));
	Health_Bar->LoadSprite("health_bar");
	Health_Bar->SetLayer(25);
}

//void GameUI::Update(float deltaTime)
//{
//	UserInterface::Update(deltaTime);
//
//	Player* player = Cast<Player>(GameplayStatics::GetController());
//
//	if (player->GetHealth() == 1)
//	{
//		lowHealthFlag += deltaTime * lowHealthDir * 100;
//		if (FMath::Abs(lowHealthFlag - 150) > 100)
//		{
//			lowHealthDir = -lowHealthDir;
//			lowHealthFlag += deltaTime * lowHealthDir * 100;
//		}
//	}
//	else if (player->GetHealth() == 0)
//	{
//		lowHealthDir = -1;
//		lowHealthFlag += deltaTime * lowHealthDir * 200;
//	}
//	else
//	{
//		lowHealthFlag = 75;
//	}
//	LowHealth->SetTransparency(player->GetHealth() <= 1 ? BYTE(lowHealthFlag < 0 ? 0 : lowHealthFlag) : 0);
//
//	if (bRecover)
//	{
//		if (Black->GetTransparency() < 250)Black->SetTransparency(Black->GetTransparency() + 25);
//	}
//	else
//	{
//		if (Black->GetTransparency() > 0)Black->SetTransparency(Black->GetTransparency() - 5);
//	}
//}
//
//void GameUI::WhiteBlink(int32 step)
//{
//	White->SetTransparency(240);
//	blinkStep = step;
//}
//
//void GameUI::BloodLoad(int i)
//{
//	Health[i]->GetAnimator()->SetNode("load");
//	IdleBlink.Reset();
//}
//
//void GameUI::BloodMinus(int i)
//{
//	Health[i]->GetAnimator()->SetNode("minus");
//	IdleBlink.Reset();
//}
//
//void GameUI::SilkLoad(int i)
//{
//	Silk[i]->GetAnimator()->SetNode("load");
//}
//
//void GameUI::SilkMinus(int i)
//{
//	Silk[i]->GetAnimator()->SetNode("minus");
//}
//
//void GameUI::SoulLoad()
//{
//	Soul->GetAnimator()->SetNode("load");
//}
//
//void GameUI::SoulMinus()
//{
//	Soul->GetAnimator()->SetNode("minus");
//}

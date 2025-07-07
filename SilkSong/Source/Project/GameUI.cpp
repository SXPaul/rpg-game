#include "GameUI.h"
#include "Player.h"
#include "GameplayStatics.h"

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

void GameUI::Update(int32 current_life, int32 max_life)
{
	Health_Bar->SetRelativeScale(FVector2D((current_life * 1.0f) / max_life, 1.f));
	Health_Bar->SetRelativePosition(FVector2D(20 + (current_life * 100.f) / max_life, 40));
}
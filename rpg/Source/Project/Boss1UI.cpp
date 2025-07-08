#include "Boss1UI.h"
#include "Player.h"
#include "GameplayStatics.h"

Boss1UI::Boss1UI()
{
	Bar = AddWidget<Image>();
	Bar->AttachTo(rootCanvas);
	//Bar->SetLayoutPattern(LayoutPattern::Center);
	Bar->SetRelativePosition(FVector2D(750, 40));
	Bar->LoadSprite("bar");
	Bar->SetLayer(24);

	Bar_Background = AddWidget<Image>();
	Bar_Background->AttachTo(rootCanvas);
	Bar_Background->SetRelativePosition(FVector2D(750, 40));
	Bar_Background->LoadSprite("bar_background");
	Bar_Background->SetLayer(24);

	Health_Bar = AddWidget<Image>();
	Health_Bar->AttachTo(rootCanvas);
	Health_Bar->SetRelativePosition(FVector2D(750, 40));
	Health_Bar->LoadSprite("health_bar");
	Health_Bar->SetLayer(25);
}
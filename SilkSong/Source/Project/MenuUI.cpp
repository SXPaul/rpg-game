#include "MenuUI.h"
#include "GameplayStatics.h"
#include "frame.h"
#include "Effect.h"
#include "MenuController.h"
//#include "VolumeUI.h"
#include "GameModeHelper.h"


MenuUI::MenuUI()
{
	Title = AddWidget<Image>();
	Title->AttachTo(rootCanvas);
	Title->SetLayoutPattern(LayoutPattern::Center);
	Title->SetRelativePosition(FVector2D(0, -175));
	Title->SetSize(FVector2D(500, 275));
	Title->LoadSprite("carpet_1");
	Title->SetLayer(10);

	Black = AddWidget<Image>();
	Black->AttachTo(rootCanvas);
	Black->SetLayoutPattern(LayoutPattern::Center);
	Black->SetSize(FVector2D(WIN_WIDTH + 20, WIN_HEIGHT + 10));
	Black->LoadSprite("carpet_3");
	Black->SetLayer(12);
	Black->SetTransparency(0);

	float delta[3] = { 240,240,240 };

	for (int i = 0; i < 3; i++)
	{
		Buttons[i] = AddWidget<Button>();
		Buttons[i]->AttachTo(Title);
		Buttons[i]->SetLayoutPattern(LayoutPattern::MiddleBottom);
		Buttons[i]->SetRelativePosition(FVector2D(0, 100 * i + 70));
		Buttons[i]->SetSize(FVector2D(delta[i] * 1.5f, 50));
		Buttons[i]->SetLayer(12);

		FVector2D pos = GameplayStatics::ProjectScreenToWorld(Buttons[i]->GetScreenPosition());
		Buttons[i]->OnMouseHoverBegin.AddLambda([=]() {
			GameplayStatics::CreateObject<Frame>(pos)->SetLocalScale(FVector2D(-1, 1));
			//GameModeHelper::PlayFXSound("sound_change_selection");
			});
		Buttons[i]->OnMouseHoverEnd.AddLambda([=]() {
			for (auto& obj : GameplayStatics::FindObjectsOfClass<Frame>())
				obj->Destory();
			});
		Buttons[i]->OnMousePressedBegin.AddLambda([=]() {
			//Effect* effect = GameplayStatics::CreateObject<Effect>(pos);
			//effect->SetLocalScale(FVector2D(0.75, 0.75));
			//effect->Init("menuhit", -0.03f);
			startFlag = i + 1;
			//for (auto& obj : GameplayStatics::FindObjectsOfClass<Pointer>())
			//{
			//	obj->FadeOut();
			//}
			//if (i == 0) GameModeHelper::PlayFXSound("sound_save");
			//GameModeHelper::PlayFXSound("sound_button_confirm");
			});

		Options[i] = AddWidget<Text>();
		Options[i]->AttachTo(Buttons[i]);
		Options[i]->SetLayoutPattern(LayoutPattern::Center);
		Options[i]->SetLayer(10);
		Options[i]->SetPattern(CharactersPattern::Middle);
		Options[i]->SetRelativePosition(FVector2D(0, 2));
	}

	Options[0]->SetText("$0START GAME", 8, "Syne Mono");
	Options[1]->SetText("$0ACHIEVEMENTS", 8, "Syne Mono");
	Options[2]->SetText("$0QUIT GAME", 8, "Syne Mono");

	//volumeUI = GameplayStatics::CreateUI<VolumeUI>();
	//volumeUI->SetOwner(this);
}

void MenuUI::Update(float deltaTime)
{
	UserInterface::Update(deltaTime);

	if (startFlag)
	{
		if (startFlag == 1 || startFlag == 5)
		{
			BYTE trans = Black->GetTransparency();
			Black->SetTransparency(trans + 2);
			if (trans < 250)
			{
				return;
			}
		}

		switch (startFlag)
		{
		case 1:GameplayStatics::OpenLevel("LevelA");
			//case 1:GameplayStatics::OpenLevel("Demo"); // Saure
			//GameModeHelper::GetInstance()->GetAudioPlayer(0)->Stop("menu");
			//GameModeHelper::GetInstance()->GetAudioPlayer(0)->Stop("menu_");
			break;
		case 3:GameplayStatics::QuitGame();
			break;
		default:
			break;
		}
	}
}
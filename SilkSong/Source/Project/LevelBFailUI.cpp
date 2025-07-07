#include "LevelBFailUI.h"
#include "PlatForm.h"
#include "GameplayStatics.h"
#include "frame.h"
#include "Effect.h"
#include "LevelBFailController.h"
#include "GameModeHelper.h"


LevelBFailUI::LevelBFailUI()
{
	Title = AddWidget<Image>();
	Title->AttachTo(rootCanvas);
	Title->SetLayoutPattern(LayoutPattern::Center);
	Title->SetRelativePosition(FVector2D(0, -175));
	Title->SetSize(FVector2D(800, 150));
	//Title->LoadSprite("");
	//Title->SetLayer(0);

	Black = AddWidget<Image>();
	Black->AttachTo(rootCanvas);
	Black->SetLayoutPattern(LayoutPattern::Center);
	Black->SetSize(FVector2D(WIN_WIDTH + 20, WIN_HEIGHT + 10));
	Black->LoadSprite("carpet_3");
	Black->SetLayer(12);
	Black->SetTransparency(0);

	float delta = 240;

	for (int i = 0; i < 3; i++)
	{
		Buttons[i] = AddWidget<Button>();
		Buttons[i]->AttachTo(Title);
		Buttons[i]->SetLayoutPattern(LayoutPattern::MiddleBottom);
		Buttons[i]->SetRelativePosition(FVector2D(0, 100 * i + 100));
		Buttons[i]->SetSize(FVector2D(delta * 1.5f, 50));
		Buttons[i]->SetLayer(12);

		FVector2D pos = GameplayStatics::ProjectScreenToWorld(Buttons[i]->GetScreenPosition());
		Buttons[i]->OnMouseHoverBegin.AddLambda([=]() {
			GameplayStatics::CreateObject<Frame>(pos)->SetLocalScale(FVector2D(-1, 1));
			});
		Buttons[i]->OnMouseHoverEnd.AddLambda([=]() {
			for (auto& obj : GameplayStatics::FindObjectsOfClass<Frame>())
				obj->Delete();
			});
		Buttons[i]->OnMousePressedBegin.AddLambda([=]() {
			//Effect* effect = GameplayStatics::CreateObject<Effect>(pos);
			//effect->SetLocalScale(FVector2D(0.75, 0.75));
			//effect->Init("menuhit", -0.03f);
			startFlag = i + 1;
			for (auto& obj : GameplayStatics::FindObjectsOfClass<Frame>())
			{
				obj->Delete();
			}
			});

		Options[i] = AddWidget<Text>();
		Options[i]->AttachTo(Buttons[i]);
		Options[i]->SetLayoutPattern(LayoutPattern::Center);
		Options[i]->SetLayer(10);
		Options[i]->SetPattern(CharactersPattern::Middle);
		Options[i]->SetRelativePosition(FVector2D(0, 2));
	}
	Text* game_name = AddWidget<Text>();
	game_name->SetRelativePosition(FVector2D(450, 120));
	game_name->SetText("$9You die!", 25, "Nerko One");
	game_name->SetLayer(11);
	PlatForm* temp;
	Options[0]->SetText("$7START GAME", 10, "Syne Mono");
	//temp = GameplayStatics::CreateObject<PlatForm>({ 0, 0 });
	//temp->Init("UI_background", { 50, 50 }, {});
	//temp->SetLocalScale({ 360.f / 50.0f, 50.f / 50.0f });
	Options[1]->SetText("$7CONTINUE", 10, "Syne Mono");
	//temp = GameplayStatics::CreateObject<PlatForm>({ 0, 100 });
	//temp->Init("UI_background", { 50, 50 }, {});
	//temp->SetLocalScale({ 360.f / 50.0f, 50.f / 50.0f });
	Options[2]->SetText("$7QUIT GAME", 10, "Syne Mono");
	//temp = GameplayStatics::CreateObject<PlatForm>({ 0, 200 });
	//temp->Init("UI_background", { 50, 50 }, {});
	//temp->SetLocalScale({ 360.f / 50.0f, 50.f / 50.0f });

	//volumeUI = GameplayStatics::CreateUI<VolumeUI>();
	//volumeUI->SetOwner(this);
}

void LevelBFailUI::Update(float deltaTime)
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
		case 1:GameplayStatics::OpenLevel("Start");
			break;
		case 2:GameplayStatics::OpenLevel("LevelB");
			break;
		case 3:GameplayStatics::QuitGame();
			break;
		default:
			break;
		}
	}
}
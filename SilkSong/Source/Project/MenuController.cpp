#include "MenuController.h"
#include "MenuUI.h"
#include "GameplayStatics.h"
#include "GameModeHelper.h"
#include "Components/ParticleSystem.h"



MenuController::MenuController()
{
}

void MenuController::BeginPlay()
{
	Super::BeginPlay();
	GameplayStatics::CreateUI<MenuUI>()->AddToViewport();
	//GameModeHelper::PlayBGMusic("menu_");
}

void MenuController::Update(float deltaTime)
{
	Super::Update(deltaTime);
}
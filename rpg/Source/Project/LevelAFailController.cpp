#include "LevelAFailController.h"
#include "LevelAFailUI.h"
#include "GameplayStatics.h"
#include "GameModeHelper.h"
#include "Components/ParticleSystem.h"



LevelAFailController::LevelAFailController()
{
}

void LevelAFailController::BeginPlay()
{
	Super::BeginPlay();
	GameplayStatics::CreateUI<LevelAFailUI>()->AddToViewport();
	//GameModeHelper::PlayBGMusic("menu_");
}

void LevelAFailController::Update(float deltaTime)
{
	Super::Update(deltaTime);
}
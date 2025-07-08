#include "LevelBFailController.h"
#include "LevelBFailUI.h"
#include "GameplayStatics.h"
#include "GameModeHelper.h"
#include "Components/ParticleSystem.h"



LevelBFailController::LevelBFailController()
{
}

void LevelBFailController::BeginPlay()
{
	Super::BeginPlay();
	GameplayStatics::CreateUI<LevelBFailUI>()->AddToViewport();
	//GameModeHelper::PlayBGMusic("menu_");
}

void LevelBFailController::Update(float deltaTime)
{
	Super::Update(deltaTime);
}
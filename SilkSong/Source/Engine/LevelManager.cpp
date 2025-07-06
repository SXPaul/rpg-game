#include "LevelManager.h"
#include "Core/World.h"

//************************************************
//*********       用户需编辑部分          **********

/**
 * 自定义场景地图头文件
 **/

#include "MenuLevel.h"
#include "boss1level.h"
#include "FirstLevel.h"
#include "StartLevel.h"
#include "LevelA.h"
#include "LevelB.h"

void LevelManager::Initialize()
{
	/**
	 * 添加场景
	 **/
	 //AddLevel<MenuLevel>("Menu");
	 //AddLevel<StartLevel>("Start");

	 /*
	 AddLevel<TearCityLevel>("TearCity");
	 AddLevel<RuinHouseLevel>("RuinHouse");
	 AddLevel<BossLevel>("BossHouse");
	 AddLevel<GrimmLevel>("GrimmTent");
	 SetDefaultLevel("Menu");
	 */
	 //*********                             **********
	 //************************************************

	AddLevel<MenuLevel>("Menu");
	AddLevel<FirstLevel>("First");
	AddLevel<StartLevel>("Start");
	AddLevel<boss1level>("Boss1");
	AddLevel<level_a>("LevelA");
	AddLevel<level_b>("LevelB");


	//level_to_create = levelMap["Boss1"]; // Example: Assign a valid callable from the map
<<<<<<< HEAD
	//SetDefaultLevel("LevelB");
=======
	SetDefaultLevel("LevelA");
>>>>>>> refs/remotes/origin/master
	//SetDefaultLevel("Boss1");
	SetDefaultLevel("Menu");

	mainWorld.currentLevel = level_to_create();
	mainWorld.currentLevel->BeginPlay();
}

void LevelManager::SetDefaultLevel(std::string levelName)
{
	level_to_delete = mainWorld.currentLevel;
	if (levelMap.find(levelName) == levelMap.end())return;
	level_to_create = levelMap[levelName];
}

void LevelManager::RefreshLevel()
{
	if (level_to_delete)
	{
		level_to_delete->OnLevelDelete();
		mainWorld.WipeData();
		delete level_to_delete;
		level_to_delete = nullptr;
		mainWorld.currentLevel = level_to_create();
		mainWorld.currentLevel->OnLevelLoad();
		mainWorld.currentLevel->BeginPlay();
	}
}

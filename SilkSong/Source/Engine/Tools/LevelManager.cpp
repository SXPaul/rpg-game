#include "LevelManager.h"
#include "Core/World.h"

//************************************************
//*********       �û���༭����          **********

/**
 * �Զ��峡����ͼͷ�ļ�
 **/
 /*
 #include "TearCityLevel.h"
 #include "MenuLevel.h"
 #include "StartLevel.h"
 #include "RuinHouseLevel.h"
 #include "BossLevel.h"
 #include "GrimmLevel.h"

 */

#include "FirstLevel.h"
#include "StartLevel.h"

void LevelManager::Initialize()
{
	/**
	 * ��ӳ���
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

	AddLevel<FirstLevel>("First");
	AddLevel<StartLevel>("Start");

	level_to_create = levelMap["First"]; // Example: Assign a valid callable from the map

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

#include "LevelManager.h"
#include "Core/World.h"

//************************************************
//*********       �û���༭����          **********

/**
 * �Զ��峡����ͼͷ�ļ�
 **/

#include "MenuLevel.h"
#include "LevelA.h"
#include "LevelAFail.h"
#include "LevelB.h"
#include "LevelBFail.h"
#include "boss1level.h"
//#include "LevelBossFail.h"
//#include "LevelBossSucceed.h"

void LevelManager::Initialize()
{
	/**
	 * ���ӳ���
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
	AddLevel<level_a>("LevelA");
	AddLevel<level_a_fail>("LevelAFail");
	AddLevel<level_b>("LevelB");
	AddLevel<level_b_fail>("LevelBFail");
	AddLevel<boss1level>("Boss");
	//AddLevel<level_boss_fail>("LevelBossFail");


	//level_to_create = levelMap["Boss1"]; // Example: Assign a valid callable from the map
	//SetDefaultLevel("Menu");
	//SetDefaultLevel("LevelA");
	//SetDefaultLevel("LevelB");
	SetDefaultLevel("Boss");

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

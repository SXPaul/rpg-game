/**
 * @file	LevelManager.h
 * @brief   ��ͼ���������壬���ڹ�����Ϸ���г�����ͼ
 * @author	Arty
 **/


#pragma once
#include <unordered_map>
#include <string>
#include <functional>

class Level;


/*----------------------------------
			   ��ͼ������
  ----------------------------------*/
class LevelManager
{
	friend class World;
public:
	void Initialize();

	void SetDefaultLevel(std::string levelName);

	void RefreshLevel();
private:
	std::unordered_map<std::string, std::function<Level*()>>levelMap;

	template<class T>
	void AddLevel(std::string levelName);

	Level* level_to_delete = nullptr;

	std::function<Level*()>level_to_create;
};

template<class T>
inline void LevelManager::AddLevel(std::string levelName)
{
	levelMap.insert({ levelName,[]() { return new T(); } });
}

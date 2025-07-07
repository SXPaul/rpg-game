/**
 * @file	CollisionManager.h
 * @brief   ��ײ���������壬���ڹ�����ײ��
 * @author	Arty
 **/


#pragma once
#include <unordered_map>

//************************************************
//*********       �û���༭����          **********

/* ��ײ���� */
///����ע��ö�����ֵ���ó���31
enum class CollisionType :uint8_t
{
	Default,
	Player,
	HurtBox,
	Enemy,
	Block,
	Item,
	Treasure,
	Dart,
	Bullet
};

//*********                             **********
//************************************************



/*----------------------------------
			  ��ײ������
  ----------------------------------*/
class CollisionManager
{
public:
	CollisionManager();

	void Initialize();

	bool LayerMaskJudge(int layerMask1, CollisionType type2);

	int FindMapping(CollisionType type);

private:
	std::unordered_map<CollisionType, int>layerMaskMap;

	void AddMapping(CollisionType type1, CollisionType type2);
};

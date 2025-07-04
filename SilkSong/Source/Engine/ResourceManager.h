/**
 * @file	ResourceManager.h
 * @brief   ��Դ���������壬���ڷ��ʲ�����ȫ����Ϸͼ��ý����Դ
 * @author	Arty
 **/

#pragma once
#include <unordered_map>
#include <vector>
#include "Core/Struct.h"



class IMAGE;

/* ������Դ�� */
namespace ArtyEngine
{
	struct FAnimationResource
	{
		IMAGE** images;
		int32 num;
	};
}

/*----------------------------------
			 ��Դ������
  ----------------------------------*/
class ResourceManager
{
public:
	void Initialize();

	IMAGE* Fetch(std::string name);
	ArtyEngine::FAnimationResource FetchAnimation(std::string name);
    std::wstring FetchVideo(std::string name);

private:
	std::unordered_map<std::string, IMAGE*>imagePool;
	std::unordered_map<std::string, ArtyEngine::FAnimationResource>animationPool;
	std::unordered_map<std::string, std::string>audioPool;
	std::unordered_map<std::string, std::wstring>videoPool;

	/**
	 * @brief ���ص���ͼ����Դ
	 * @param[in] name			    ָ����Դ����
	 * @param[in] path              ��Դ·��
	 * @param[in] wid			    ͼ����
	 * @param[in] hei	            ͼ��߶� 
	 **/
	void Load(std::string name, std::string path, int wid, int hei);

	/**
	 * @brief ���ض��Ŷ���ͼ����Դ
	 * @param[in] name			    ָ����Դ����
	 * @param[in] path              ��Դ·��
	 * @param[in] wid			    ͼ����
	 * @param[in] hei	            ͼ��߶�
	 * @param[in] hei	            ����֡����
	 **/
	void Load(std::string name, std::string path, int wid, int hei, int num);

	/**
	 * @brief ���ض��Ŷ���ͼ����Դ
	 * @param[in] name			    ָ����Դ����
	 * @param[in] path              ��Դ·��
	 * @param[in] arr			    ����һ��Pair���飬����ָ��ÿһ֡�����Ŀ����߶�
	 **/
	void Load(std::string name, std::string path, const std::vector<FIntVector2>& arr);

	/**
	 * @brief ����SpriteSheet����ͼ����Դ
	 * @param[in] name			    ָ����Դ����
	 * @param[in] path              ��Դ·��
	 * @param[in] wid			    SpriteSheet���
	 * @param[in] hei	            SpriteSheet�߶�
	 * @param[in] row	            SpriteSheet����
	 * @param[in] col	            SpriteSheet����
	 **/
	void Load(std::string name, std::string path, int wid, int hei, int num, int row, int col);

	//������Ƶý����Դ
	void Load(std::string name, std::string path);

	//������Ƶ��Դ
	void Load(std::string name, std::wstring pszFileName);

	//����������Դ
	void LoadText(std::string path);

	//���������ʽ��Դ
	void LoadCustomCursor(std::string path);
};
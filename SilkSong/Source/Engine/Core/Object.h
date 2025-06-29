/**
 * @file	Object.h
 * @brief	��Ϸ�����ඨ�壬ObjectΪ���������Ļ���
 * @author	Arty
 **/

#pragma once
#include<iostream>
#include<string>



/*----------------------------------
			  ����������
  ----------------------------------*/
class Object 
{
	static int number;

	std::string name;

public:
	Object() { number++; InitName(std::string(typeid(*this).name()).substr(6)); }
	virtual ~Object() { number--; }

	//��ʼ����ǩ��
	void InitName(const std::string& name) 
	{ 
		this->name = name + std::string("_") + std::to_string(number);
	}

	//��ȡ��ǩ��
	std::string GetName()const { return name; }

	//���ñ�ǩ��
	void SetName(const std::string& name) { this->name = name; }

	virtual void Update(float deltaTime) {}

	virtual void BeginPlay() {}

	//��ֹ�û��Զ�����������������ʹ�øú���
	virtual void EndPlay() {}
};



/*----------------------------------
			 ȫ����Ϸ����
  ----------------------------------*/
class GameInstance
{
public:
	GameInstance();
};
#pragma once
#include "UI/UserInterface.h"

class Pointer;

class LevelBFailUI :public UserInterface
{
	Image* Title;
	Image* Black;

	Text* Options[3];
	Button* Buttons[3];

	int32 startFlag = 0;

	class VolumeUI* volumeUI;
public:
	LevelBFailUI();

	virtual void Update(float deltaTime)override;
};
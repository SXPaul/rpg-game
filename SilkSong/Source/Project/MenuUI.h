#pragma once
#include "UI/UserInterface.h"

class Pointer;

class MenuUI :public UserInterface
{
	Image* Title;
	Image* Black;

	Text* Options[3];
	Button* Buttons[3];

	int32 startFlag = 0;

	class VolumeUI* volumeUI;
public:
	MenuUI();

	virtual void Update(float deltaTime)override;
};
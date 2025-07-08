#pragma once
#include "UI/UserInterface.h"
#include "Components/Animator.h"


class GameUI :public UserInterface
{
	Image* Bar;
	Image* Bar_Background;
	Image* Health_Bar;

public:
	GameUI();
	void Update(int32 current_life, int32 max_life);
};
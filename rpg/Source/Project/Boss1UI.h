#pragma once
#include "UI/UserInterface.h"
#include "Components/Animator.h"


class Boss1UI :public UserInterface
{
	Image* Bar;
	Image* Bar_Background;
	Image* Health_Bar;

public:
	Boss1UI();
};
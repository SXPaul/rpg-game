#pragma once
#include "UI/UserInterface.h"
#include "Components/Animator.h"


class GameUI :public UserInterface
{
	Image* Bar;
	Image* Bar_Background;
	Image* Health_Bar;
	//Image* LowHealth;
	//Image* Black;

	//Image* SoulContainer;
	//Image* SoulContainer_;
	//Image* SilkContainer;

	//Image* Health[5];
	//Animation bloodidle[5];
	//Animation bloodload[5];
	//Animation bloodminus[5];
	//Timer IdleBlink;

	//Image* Soul;
	//Animation soulload;
	//Animation soulminus;

	//Sector* ItemSector;
	//Image* Dart;

	//int32 blinkStep = 1;

	//float lowHealthFlag = 50;

	//int32 lowHealthDir = 1;

	//bool bRecover = false;

public:
	GameUI();

	//virtual void Update(float deltaTime)override;

	//void WhiteBlink(int32 step);

	//void BlackInterval(bool enable) { bRecover = enable; }

	//void BloodLoad(int i);

	//void BloodMinus(int i);

	//void SilkLoad(int i);

	//void SilkMinus(int i);

	//void SoulLoad();

	//void SoulMinus();
};
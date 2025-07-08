#pragma once
#include "Objects/Level.h"


class StartLevel :public Level
{
public:
	StartLevel();
	void Update(float deltaTime);
};
#pragma once
#include "Objects/Character.h"

class LevelBFailController :public Controller
{
	DEFINE_SUPER(Controller)

public:
	LevelBFailController();

	virtual void BeginPlay()override;

	virtual void Update(float deltaTime)override;
};
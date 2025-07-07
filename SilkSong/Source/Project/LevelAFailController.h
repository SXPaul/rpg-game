#pragma once
#include "Objects/Character.h"




class LevelAFailController :public Controller
{
	DEFINE_SUPER(Controller)

public:
	LevelAFailController();

	virtual void BeginPlay()override;

	virtual void Update(float deltaTime)override;
};
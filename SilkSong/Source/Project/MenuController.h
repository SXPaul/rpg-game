#pragma once
#include "Objects/Character.h"




class MenuController :public Controller
{
	DEFINE_SUPER(Controller)

public:
	MenuController();

	virtual void BeginPlay()override;

	virtual void Update(float deltaTime)override;
};
/**
 * @file	WidgetComponent.h
 * @brief	С������������ڽ���ĻUI������������
 * @author	Arty
 **/

#pragma once
#include"Components/SceneComponent.h"



class UserInterface;

 /*----------------------------------
			   С�������
   ----------------------------------*/
class WidgetComponent final : public SceneComponent
{
	DEFINE_SUPER(SceneComponent)

public:
	WidgetComponent();

	virtual void Update(float deltaTime)override;

	virtual void Activate()override;

	virtual void Deactivate()override;

	void SetUI(UserInterface* ui);

	UserInterface* GetUI() { return userInterface; }

	void SetSize(FVector2D size);

	virtual void RegisterDontDestroy()override;

private:
	UserInterface* userInterface;
};
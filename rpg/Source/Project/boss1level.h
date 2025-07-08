// Source/Project/NewLevel.h
#pragma once
#include "Objects/Level.h"

class boss1level : public Level
{
public:
    boss1level();

    virtual void Update(float deltaTime) override;
    void Draw_Platform(float x, float y);
};
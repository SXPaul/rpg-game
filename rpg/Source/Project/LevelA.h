// Source/Project/NewLevel.h
#pragma once
#include "Objects/Level.h"

class level_a : public Level
{
public:
    level_a();

    virtual void Update(float deltaTime) override;
};
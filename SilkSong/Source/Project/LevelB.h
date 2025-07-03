// Source/Project/NewLevel.h
#pragma once
#include "Objects/Level.h"

class level_b : public Level
{
public:
    level_b();

    virtual void Update(float deltaTime) override;
};
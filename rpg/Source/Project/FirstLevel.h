#pragma once
#include "Objects/Level.h"

class FirstLevel : public Level
{
    DEFINE_SUPER(Level)
public:
    FirstLevel();
    virtual void BeginPlay() override;
};
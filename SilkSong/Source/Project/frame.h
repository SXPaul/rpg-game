#pragma once
#include "Objects/Actor.h"
#include "Components/SpriteRenderer.h"

class Frame : public Actor
{
public:
    Frame();
    void Delete();

protected:
    class SpriteRenderer* render;
};
#include "frame.h"
#include "Objects/Actor.h"

Frame::Frame()
{
    render = ConstructComponent<SpriteRenderer>();
    SetRootComponent(render);
    render->LoadSprite("red_1");
    render->SetLayer(10);
}

void Frame::Delete()
{
    render->LoadSprite("");
}
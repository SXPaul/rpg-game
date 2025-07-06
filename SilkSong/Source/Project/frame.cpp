#include "frame.h"

Frame::Frame()
{
    render = ConstructComponent<SpriteRenderer>();
    SetRootComponent(render);
    render->LoadSprite("red_1");
    render->SetLayer(10);
}

void Frame::Delete()
{
    this->Destory();
}
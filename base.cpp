#include <SDL.h>
#include "base.h"

base::base(SDL_Renderer* renderer)
{
    this->renderer = renderer;
    x=0;
    y=0;
    width=1;
    height=1;
}

base::~base()
{

}

void base::Render()
{

}


bool base::is_collide(base* base2)
{
    if (x + width > base2->x && x < base2->x + base2->width &&
        y + height > base2->y && y < base2->y + base2->height)
    {
        return true;
    }
    return false;
}

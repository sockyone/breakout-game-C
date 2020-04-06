#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED
#include <SDL.h>

class base
{
protected:
    SDL_Renderer* renderer;
public:
    float x;
    float y;
    int width;
    int height;
    base(SDL_Renderer* renderer);
    virtual ~base();
    virtual void Render();
    bool is_collide(base* base2);

};


#endif // BASE_H_INCLUDED

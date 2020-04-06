#ifndef PAD_H_INCLUDED
#define PAD_H_INCLUDED

#include "base.h"
#include <SDL.h>

class pad : public base
{
private:
    SDL_Texture* pad_texture;
public:
    pad(SDL_Renderer* renderer);
    ~pad();

    void Update(float count_tick);
    void Render();

};

#endif // PAD_H_INCLUDED

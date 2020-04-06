#ifndef LOADSCREEN_H_INCLUDED
#define LOADSCREEN_H_INCLUDED

#include "base.h"

class loadscreen : public base
{
private:
    SDL_Texture* screen;
    SDL_Texture* start_screen;
    SDL_Texture* quit_screen;
    int status;
public:
    loadscreen(SDL_Renderer* renderer);
    ~loadscreen();
    void Render();
    int Update(bool &state);
};


#endif // LOADSCREEN_H_INCLUDED

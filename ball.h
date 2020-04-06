#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SDL.h>
#include "base.h"
#include <iostream>


class ball : public base
{
private:
    SDL_Texture* ball_texture;
    float BALL_SPEED;
public:
    float dirx;
    float diry;

    ball(SDL_Renderer* renderer);
    ~ball();
    void Update(float count_tick);
    void Render();
    void set_direction(float dirx, float diry);
    void set_ballspeed(float x);
    float get_ballspeed();

};

#endif // BALL_H_INCLUDED

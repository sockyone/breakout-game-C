#ifndef DETAILS_H_INCLUDED
#define DETAILS_H_INCLUDED

#include "base.h"
#include <SDL_ttf.h>
#include <sstream>
#include <iostream>
#include <string>

class details : public base
{
private:
    SDL_Texture* back_ground;
    float ball_speed;
    int brick_left;
    int level;
    int turn_left;
    SDL_Rect level_rect;
    SDL_Rect ballspeed_rect;
    SDL_Rect brick_rect;
    SDL_Rect turn_rect;
    TTF_Font* font;
    SDL_Color textColor;
public:
    details(SDL_Renderer* renderer);
    ~details();
    void Update(float ball_speed,int brick_left,int level,int turn_left);
    void Render();
    void level_text_init();
    void turn_text_init();
    void brickleft_text_init();
    void ballspeed_text_init();
};


#endif // DETAILS_H_INCLUDED

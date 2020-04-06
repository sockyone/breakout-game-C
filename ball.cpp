#include "ball.h"
#include <SDL.h>
#include <math.h>

ball::ball(SDL_Renderer* renderer) : base(renderer)
{
    SDL_Surface* surface_temp = SDL_LoadBMP("ball.bmp");
    ball_texture = SDL_CreateTextureFromSurface(renderer,surface_temp);
    SDL_FreeSurface(surface_temp);

    x=0;
    y=0;
    BALL_SPEED = 550.0f;

    width = 24;
    height = 24;
    set_direction(1,-1);
}

ball::~ball()
{
    SDL_DestroyTexture(ball_texture);
    ball_texture = NULL;
}

void ball::Render()
{
    SDL_Rect rect_temp;
    rect_temp.x = (int)(x+0.5f);
    rect_temp.y = (int)(y+0.5f);
    rect_temp.w = width;
    rect_temp.h = height;

    SDL_RenderCopy(renderer,ball_texture,NULL,&rect_temp);
}

void ball::Update(float count_tick)
{
    this->x += dirx*count_tick;
    this->y += diry*count_tick;
    if ((this->y) < 0) this->y=0;
}

void ball::set_direction(float dirx,float diry)
{
    //do dai chuan
    float right_length = sqrt(dirx*dirx + diry*diry);
    this->dirx = BALL_SPEED * (dirx / right_length);
    this->diry = BALL_SPEED * (diry / right_length);
}

void ball::set_ballspeed(float x)
{
    this->BALL_SPEED = x;
}

float ball::get_ballspeed()
{
    return this->BALL_SPEED;
}

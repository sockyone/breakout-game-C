#include "pad.h"
#include <SDL.h>

pad::pad(SDL_Renderer* renderer) : base(renderer)
{
    SDL_Surface* surface_temp = SDL_LoadBMP("pad.bmp");
    pad_texture = SDL_CreateTextureFromSurface(renderer,surface_temp);
    SDL_FreeSurface(surface_temp);

    x=200;
    y=600-32;

    width=128;
    height=32;
}

pad::~pad()
{
    SDL_DestroyTexture(pad_texture);
    pad_texture = NULL;
}


void pad::Render()
{
    SDL_Rect rect_temp;
    rect_temp.x = (int)(x+0.5f);
    rect_temp.y = (int)(y+0.5f);
    rect_temp.w = width;
    rect_temp.h = height;

    SDL_RenderCopy(renderer,pad_texture,NULL,&rect_temp);
}


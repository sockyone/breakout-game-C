#include "endgame.h"
#include <sstream>
#include <math.h>

endgame::endgame(SDL_Renderer* renderer) : base(renderer)
{
    SDL_Surface* surface_temp = SDL_LoadBMP("win_screen.bmp");
    win_screen = SDL_CreateTextureFromSurface(renderer,surface_temp);
    surface_temp = SDL_LoadBMP("lose_screen.bmp");
    lose_screen = SDL_CreateTextureFromSurface(renderer,surface_temp);
    SDL_FreeSurface(surface_temp);


    textColor={255,0,0};

    x = 0;
    y = 0;
    width = 1100;
    height = 600;
    font = TTF_OpenFont("myfont.ttf",36);
    font2 = TTF_OpenFont("font.ttf",36);
}

endgame::~endgame()
{
    SDL_DestroyTexture(win_screen);
    SDL_DestroyTexture(lose_screen);
    win_screen = NULL;
    lose_screen = NULL;
}

void endgame::Update(string username,int score,bool win)
{
    this->username = username;
    this->score = score;
    this->win = win;
}

void endgame::Render()
{
    if (win)
    {
        SDL_Rect temp;
        temp.x = (int)x;
        temp.y = (int)y;
        temp.w = width;
        temp.h = height;
        SDL_RenderCopy(renderer,win_screen,NULL,&temp);

        temp.x = 100;
        temp.y = 170;
        temp.w = 35*(username.length());
        temp.h = 100;
        SDL_Surface* text_Surface = TTF_RenderText_Solid(this->font, username.c_str(),textColor);
        SDL_Texture* text_Texture = SDL_CreateTextureFromSurface(renderer,text_Surface);
        SDL_FreeSurface(text_Surface);
        SDL_RenderCopy(renderer,text_Texture,NULL,&temp);
        SDL_DestroyTexture(text_Texture);

        temp.x = 480;
        temp.y = 400;
        temp.w = 100;
        temp.h = 100;
        stringstream text;
        text.str("");
        text << score;
        text_Surface = TTF_RenderText_Solid(this->font2, text.str().c_str(),textColor);
        text_Texture = SDL_CreateTextureFromSurface(renderer,text_Surface);
        SDL_FreeSurface(text_Surface);
        SDL_RenderCopy(renderer,text_Texture,NULL,&temp);
        SDL_DestroyTexture(text_Texture);
    }
    else
    {
        SDL_Rect temp;
        temp.x = (int)x;
        temp.y = (int)y;
        temp.w = width;
        temp.h = height;
        SDL_RenderCopy(renderer,lose_screen,NULL,&temp);

        temp.x = 120;
        temp.y = 150;
        temp.w = 35*(username.length());
        temp.h = 100;
        SDL_Surface* text_Surface = TTF_RenderText_Solid(this->font, username.c_str(),textColor);
        SDL_Texture* text_Texture = SDL_CreateTextureFromSurface(renderer,text_Surface);
        SDL_FreeSurface(text_Surface);
        SDL_RenderCopy(renderer,text_Texture,NULL,&temp);
        SDL_DestroyTexture(text_Texture);

        temp.x = 520;
        temp.y = 440;
        temp.w = 100;
        temp.h = 100;
        stringstream text;
        text.str("");
        text << score;
        text_Surface = TTF_RenderText_Solid(this->font2, text.str().c_str(),textColor);
        text_Texture = SDL_CreateTextureFromSurface(renderer,text_Surface);
        SDL_FreeSurface(text_Surface);
        SDL_RenderCopy(renderer,text_Texture,NULL,&temp);
        SDL_DestroyTexture(text_Texture);
    }
}

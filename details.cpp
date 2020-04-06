#include "details.h"
#include <string>

using namespace std;

details::details(SDL_Renderer* renderer) : base(renderer)
{
    SDL_Surface* surface_temp = SDL_LoadBMP("details.bmp");
    back_ground = SDL_CreateTextureFromSurface(renderer,surface_temp);
    SDL_FreeSurface(surface_temp);
    font = TTF_OpenFont("font.ttf",12);
    textColor = {0,0,0};
    x=800;
    y=0;

    level_rect.x = int(x + 130.0f);
    level_rect.y = int(y + 53.0f);
    level_rect.w = 50;
    level_rect.h = 50;

    turn_rect.x = int(x+180.0f);
    turn_rect.y = int(y+175.0f);
    turn_rect.w = 50;
    turn_rect.h = 50;

    ballspeed_rect.x = int(x+50.0f);
    ballspeed_rect.y = int(y+360.0f);
    ballspeed_rect.w = 150;
    ballspeed_rect.h = 50;

    brick_rect.x = int(x+60.0f);
    brick_rect.y = int(y+500.0f);
    brick_rect.w = 100;
    brick_rect.h = 50;

    width = 300;
    height = 600;
}

details::~details()
{
    SDL_DestroyTexture(back_ground);
    back_ground = NULL;
}

void details::Update(float ball_speed,int brick_left,int level,int turn_left)
{
    this->ball_speed = ball_speed;
    this->brick_left=brick_left;
    this->level=level;
    this->turn_left=turn_left;
}

void details::Render()
{
    SDL_Rect rect_temp;
    rect_temp.x = (int)x;
    rect_temp.y = (int)y;
    rect_temp.w = width;
    rect_temp.h = height;

    SDL_RenderCopy(renderer,back_ground,NULL,&rect_temp);
    level_text_init();
    turn_text_init();
    ballspeed_text_init();
    brickleft_text_init();
}

void details::level_text_init()
{
    std::stringstream text;
    text.str("");
    text << level;
    if (level > 9) level_rect.w = 100;
    SDL_Surface* text_Surface = TTF_RenderText_Solid(this->font, text.str().c_str(), this->textColor);
    if (text_Surface == NULL) cout << "Surface Init error";
    SDL_Texture* text_Texture = SDL_CreateTextureFromSurface(renderer,text_Surface);
    if (text_Texture == NULL)
    {
        cout << "Texture Init error\n" << SDL_GetError() << endl;
    }
    SDL_FreeSurface(text_Surface);
    SDL_RenderCopy(renderer,text_Texture,NULL,&level_rect);
    SDL_DestroyTexture(text_Texture);
}

void details::turn_text_init()
{
    std::stringstream text;
    text.str("");
    text << this->turn_left;
    SDL_Surface* text_Surface = TTF_RenderText_Solid(this->font, text.str().c_str(), this->textColor);
    SDL_Texture* text_Texture = SDL_CreateTextureFromSurface(renderer,text_Surface);
    SDL_FreeSurface(text_Surface);
    SDL_RenderCopy(renderer,text_Texture,NULL,&turn_rect);
    SDL_DestroyTexture(text_Texture);
}

void details::brickleft_text_init()
{
    std::stringstream text;
    text.str("");
    text << this->brick_left;
    if (brick_left < 10) brick_rect.w = 50;
    else brick_rect.w = 100;
    SDL_Surface* text_Surface = TTF_RenderText_Solid(this->font, text.str().c_str(), this->textColor);
    SDL_Texture* text_Texture = SDL_CreateTextureFromSurface(renderer,text_Surface);
    SDL_FreeSurface(text_Surface);
    SDL_RenderCopy(renderer,text_Texture,NULL,&brick_rect);
    SDL_DestroyTexture(text_Texture);
}

void details::ballspeed_text_init()
{
    std::stringstream text;
    text.str("");
    text << (int)this->ball_speed;
    SDL_Surface* text_Surface = TTF_RenderText_Solid(this->font, text.str().c_str(), this->textColor);
    SDL_Texture* text_Texture = SDL_CreateTextureFromSurface(renderer,text_Surface);
    SDL_FreeSurface(text_Surface);
    SDL_RenderCopy(renderer,text_Texture,NULL,&ballspeed_rect);
    SDL_DestroyTexture(text_Texture);
}

#include "loadscreen.h"

loadscreen::loadscreen(SDL_Renderer* renderer) : base(renderer)
{
    SDL_Surface* surface_temp = NULL;
    surface_temp = SDL_LoadBMP("loadgame.bmp");
    screen = SDL_CreateTextureFromSurface(renderer,surface_temp);
    surface_temp = SDL_LoadBMP("loadgame_start.bmp");
    start_screen = SDL_CreateTextureFromSurface(renderer,surface_temp);
    surface_temp = SDL_LoadBMP("loadgame_quit.bmp");
    quit_screen = SDL_CreateTextureFromSurface(renderer,surface_temp);
    SDL_FreeSurface(surface_temp);

    x = 0;
    y = 0;

    status=0;

    width = 1100;
    height = 600;
}

loadscreen::~loadscreen()
{
    SDL_DestroyTexture(screen);
    SDL_DestroyTexture(start_screen);
    SDL_DestroyTexture(quit_screen);
    screen = NULL;
    start_screen = NULL;
    quit_screen = NULL;
}

int loadscreen::Update(bool &state)
{
    bool quit=false;
    SDL_Event e;
    if (SDL_PollEvent(&e))
        if (e.type == SDL_QUIT)
        {
            quit=true;
            state = false;
        }
    int mx, my;
    Uint8 mstate = SDL_GetMouseState(&mx, &my);
    if ((mx > 720 && mx < 900) && (my > 270 && my < 325))
        status = 1;
    else if ((mx > 720 && mx < 900) && (my > 390 && my < 450))
        status = 2;
    else status = 0;

    if (e.type == SDL_MOUSEBUTTONDOWN)
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            mx = e.button.x;
            my = e.button.y;
            if ((mx > 720 && mx < 900) && (my > 270 && my < 325))
            {
                quit = true;
                state = true;
            }
            if ((mx > 720 && mx < 900) && (my > 390 && my < 450))
            {
                quit = true;
                state = false;
            }
        }
    return quit;
}

void loadscreen::Render()
{
    SDL_Rect temp;
    temp.x = (int)x;
    temp.y = (int)y;
    temp.w = width;
    temp.h = height;
    if (status==0)
        SDL_RenderCopy(renderer,screen,NULL,&temp);
    else if (status == 1)
        SDL_RenderCopy(renderer,start_screen,NULL,&temp);
    else
        SDL_RenderCopy(renderer,quit_screen,NULL,&temp);
}


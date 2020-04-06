#include <SDL.h>
#include "broad.h"
#include <random>

board::board(SDL_Renderer* renderer) : base(renderer)
{
    SDL_Surface* surface_temp = NULL;
    surface_temp = SDL_LoadBMP("red_block.bmp");
    brick_texture[RED] = SDL_CreateTextureFromSurface(renderer,surface_temp);
    surface_temp = SDL_LoadBMP("blue_block.bmp");
    brick_texture[BLUE] = SDL_CreateTextureFromSurface(renderer,surface_temp);
    surface_temp = SDL_LoadBMP("green_block.bmp");
    brick_texture[GREEN] = SDL_CreateTextureFromSurface(renderer,surface_temp);
    SDL_FreeSurface(surface_temp);

    x = 0;
    y = 0;
    width = 800;
    height = 600;

    brick_start_x = 32;
    brick_start_y = 16;
}

board::~board()
{
    for (int i=0;i<TOTAL;i++)
    {
        SDL_DestroyTexture(brick_texture[i]);
        brick_texture[i] = NULL;
    }
}


void board::Render()
{
    for (int i=0;i<brick_num_x;i++)
        for(int j=0;j<brick_num_y;j++)
    {
        if (bricks_matrix[i][j].status)
        {
            SDL_Rect rect_temp;
            rect_temp.x = int (x + brick_start_x + i*brick_w);
            rect_temp.y = int (y + brick_start_y + j*brick_h);
            rect_temp.w = brick_w;
            rect_temp.h = brick_h;
            SDL_RenderCopy(renderer,brick_texture[bricks_matrix[i][j].color],NULL,&rect_temp);
        }
    }
}

void board::CreateLevel()
{
    for (int i=0;i<brick_num_x;i++)
        for(int j=0;j<brick_num_y;j++)
        {
            bricks_matrix[i][j].color = rand()%TOTAL;
            bricks_matrix[i][j].status = rand()%2;
        }
}



#ifndef BROAD_H_INCLUDED
#define BROAD_H_INCLUDED

#include <SDL.h>
#include "base.h"

const int brick_num_x = 11;
const int brick_num_y = 10;
const int brick_w = 64;
const int brick_h = 24;

enum
{
    RED,
    BLUE,
    GREEN,
    TOTAL
};


class brick
{
public:
    bool status;
    int color;
};

class board : public base
{
private:
    SDL_Texture* brick_texture[TOTAL];
public:
    board(SDL_Renderer* renderer);
    ~board();

    void Update(float count_tick);
    void Render();
    void CreateLevel();

    int brick_start_x;
    int brick_start_y;

    brick bricks_matrix[brick_num_x][brick_num_y];
};

#endif // BROAD_H_INCLUDED

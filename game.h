#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "broad.h"
#include "ball.h"
#include "pad.h"
#include "details.h"
#include "loadscreen.h"
#include "getname.h"
#include "endgame.h"
#include <SDL.h>
#include <iostream>


const int SCREEN_WIDTH = 1100;
const int SCREEN_HEIGHT = 600;

class Game
{
public:
    Game();
    ~Game();

    bool Init();
    void Run();
    bool loadgame();
    bool getnameuser();
    void display_endgame();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;

    string username;
    int score;
    int turn_play;
    int level;
    bool win;
    unsigned int tick_last, tick_now;
    bool quit;

    board* Board;
    pad* Pad;
    ball* Ball;
    details* Details;
    loadscreen* Loadscreen;
    getname* Getname;
    endgame* Endgame;

    bool pad_start;

    void Update(float count_tick,SDL_Event e);
    void Render();

    void Clean();

    void NewGame();
    void reset_pad();
    void get_ball_reset();
    void turn_vectorX();
    void turn_vectorY();

    void pad_handle_move(float x);
    float pad_return_ball(float hitx);
    void check_collides_board();
    void check_collides_pad();
    void check_collides_brick();
    int brick_left();
    void level_handle();

};

#endif // GAME_H_INCLUDED

#include "game.h"
#include <random>
#include <time.h>

Game::Game()
{
    renderer = NULL;
    window = NULL;
    quit = false;
    turn_play=3;
    level = 10;
    win = false;
    score = 0;
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window = NULL;
    TTF_Quit();
    SDL_Quit();
}

bool Game::Init()
{
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Breakout Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Error : Can't create window: " << SDL_GetError() << std::endl;
        return false;
    }
    else
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {

        std::cout << "Error : Can't create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    TTF_Init();

    return true;
}

void Game::Clean()
{

}

void Game::NewGame()
{
    Board->CreateLevel();
    reset_pad();
    level ++;
    level_handle();
}

void Game::reset_pad()
{
    pad_start = true;
    get_ball_reset();
}

void Game::get_ball_reset()
{
    Ball->x = Pad->x + Pad->width/2 - Ball->width/2;
    Ball->y = Pad->y - Ball->height;
}

bool Game::loadgame()
{
    bool state;
    this->Loadscreen = new loadscreen(renderer);
    bool quit_=false;
    while(!quit_)
    {
        SDL_RenderClear(renderer);
        quit_=Loadscreen->Update(state);
        Loadscreen->Render();
        SDL_RenderPresent(renderer);
    }
    delete Loadscreen;
    return state;
}

void Game::Run()
{
    this->Pad = new pad(renderer);
    this->Ball = new ball(renderer);
    this->Board = new board(renderer);
    this->Details = new details(renderer);

    NewGame();
    tick_last = SDL_GetTicks();
    SDL_WarpMouseInWindow(window,400,580);
    while (!quit)
    {
        if (level == 16)
        {
            quit = true;
            win = true;
        }
        SDL_Event e;
        if (SDL_PollEvent(&e))
            if (e.type == SDL_QUIT) quit=true;
        if (turn_play <= 0) quit=true;
        tick_now = SDL_GetTicks();
        float tick_count = (tick_now-tick_last)/1000.0f;
        tick_last = tick_now;
        Update(tick_count,e);
        Render();
    }
    delete Pad;
    delete Ball;
    delete Board;
    delete Details;
}

bool Game::getnameuser()
{
    bool state = false;
    bool quit_ = false;
    getname* Getname = new getname(renderer);
    while (!quit_)
    {
        SDL_RenderClear(renderer);
        quit_ = Getname->Update(state);
        Getname->Render();
        SDL_RenderPresent(renderer);
    }
    username = Getname->get_user_name();
    delete Getname;
    return state;
}

void Game::Update(float count_tick,SDL_Event e)
{
    int mx, my;
    Uint8 mstate = SDL_GetMouseState(&mx, &my);
    pad_handle_move(mx - Pad->width/2.0f);

    if (e.type== SDL_MOUSEBUTTONDOWN)
        if (e.button.button = SDL_BUTTON_LEFT)
            if (pad_start)
            {
                pad_start = false;
                if (rand()%2)
                    Ball->set_direction(1,-1);
                else Ball->set_direction(-1,-1);
            }

    if (pad_start)
    {
        get_ball_reset();
    }

    check_collides_board();
    check_collides_pad();
    check_collides_brick();

    if (brick_left() == 0)
    {
        NewGame();
    }

    Details->Update(Ball->get_ballspeed(),brick_left(),level,turn_play);
    if(!pad_start)
        Ball->Update(count_tick);

}

void Game::Render()
{

    SDL_RenderClear(renderer);
    Pad->Render();
    Ball->Render();
    Board->Render();
    Details->Render();

    SDL_RenderPresent(renderer);
}

void Game::check_collides_pad()
{
    float ball_center_x = Ball->x + Ball->width/2.0f;
    if (Ball->is_collide(Pad))
    {
        Ball->y = Pad->y - Ball->height;
        Ball->set_direction(pad_return_ball(ball_center_x-Pad->x),-1);
    }
}

float Game::pad_return_ball(float hitx)
{
    if (hitx<0) hitx = 0;
    if (hitx > Pad->width) hitx = Pad->width;
    hitx -= Pad->width/2.0f;
    return (hitx/(Pad->width/2.0f)) * 2.0f;
}

void Game::check_collides_board()
{
    if (Ball->y <= Board->y)
    {
        Ball->y = Board->y;
        turn_vectorY();
    }
    else if (Ball->y + Ball->height > Board->y + Board->height)
    {
        reset_pad();
        turn_play--;
    }

    if (Ball->x <= Board->x)
    {
        Ball->x = Board->x;
        turn_vectorX();
    }
    else if (Ball->x + Ball->width >= Board->x+Board->width)
    {
        Ball->x = Board->x + Board->width - Ball->width;
        turn_vectorX();
    }
}

void Game::check_collides_brick()
{
    for(int i=0;i<brick_num_x;i++)
        for(int j=0;j<brick_num_y;j++)
        {
            brick brick = Board->bricks_matrix[i][j];
            if (brick.status)
            {
                float brick_x = Board->brick_start_x + i*brick_w;
                float brick_y = Board->brick_start_y + j*brick_h;
                float brick_center_x = brick_x + brick_w/2.0f;
                float brick_center_y = brick_y + brick_h/2.0f;
                float ball_center_x = Ball->x + Ball->width/2.0f;
                float ball_center_y = Ball->y + Ball->height/2.0f;

                if (fabs(brick_center_x-ball_center_x)<=0.5f*float(Ball->width+brick_w)
                    && fabs(brick_center_y-ball_center_y) <= 0.5f*float(Ball->height+brick_h))
                {
                    Board->bricks_matrix[i][j].status = false;
                    score++;
                    float y1=0;
                    float y2=0;
                    float x1=0;
                    float x2=0;
                    if (Ball->y+Ball->height > brick_y + brick_h)
                        y1 = brick_y + brick_h;
                    else
                        y1 = Ball->y + Ball->height;
                    if (Ball->y > brick_y)
                        y2 = Ball->y;
                    else
                        y2 = brick_y;
                    float vary = fabs(y2-y1);

                    if (Ball->x + Ball->width > brick_x + brick_w)
                        x1 = brick_x + brick_w;
                    else
                        x1 = Ball->x + Ball->width;

                    if (Ball->x > brick_x)
                        x2 = Ball->x;
                    else
                        x2 = brick_x;
                    float varx = fabs(x1-x2);

                    if (vary >= varx)
                    {
                        if (brick_center_x > ball_center_x)
                        {
                            if (Ball->dirx > 0)
                                turn_vectorX();
                            Ball->x -= varx;
                        }
                        else
                        {
                            if (Ball->dirx < 0)
                                turn_vectorX();
                            Ball->x += varx;
                        }
                    }
                    else
                    {
                        if (brick_center_y >= ball_center_y)
                        {
                            Ball->y -= vary;
                            if (Ball->diry > 0)
                                turn_vectorY();
                        }
                        else
                        {
                            Ball->y += vary;
                            if (Ball->diry < 0)
                                turn_vectorY();
                        }
                    }
                }
            }
        }
}

void Game::turn_vectorX()
{
    float multi = -1.0f;
    Ball->dirx = Ball->dirx * multi;
    Ball->set_direction(Ball->dirx,Ball->diry);
}

void Game::turn_vectorY()
{
    float multi = -1.0f;
    Ball->diry = Ball->diry * multi;
    Ball->set_direction(Ball->dirx,Ball->diry);
}

void Game::pad_handle_move(float x)
{
    if (x < Board->x) Pad->x = Board->x;
    else if ((x + Pad->width) > (Board->x + Board->width))
        Pad->x = Board->x + Board->width - Pad->width;
    else Pad->x = x;
}

int Game::brick_left()
{
    int count=0;
    for(int i=0;i<brick_num_x;i++)
        for(int j=0;j<brick_num_y;j++)
        {
            brick brick = Board->bricks_matrix[i][j];
            if (brick.status) count ++;
        }
    return count;
}

void Game::level_handle()
{
    if (level == 2) Ball->set_ballspeed(600.0f);
    if (level == 3) Ball->set_ballspeed(650.0f);
    if (level == 4) Ball->set_ballspeed(700.0f);
    if (level == 5) Ball->set_ballspeed(750.0f);
    if (level == 6) Ball->set_ballspeed(800.0f);
    if (level == 7) Ball->set_ballspeed(850.0f);
    if (level == 8) Ball->set_ballspeed(900.0f);
    if (level == 9) Ball->set_ballspeed(950.0f);
    if (level == 10)
    {
        Ball->set_ballspeed(1050.0f);
        turn_play++;
    }
    if (level == 11) Ball->set_ballspeed(1100.0f);
    if (level == 12) Ball->set_ballspeed(1150.0f);
    if (level == 13) Ball->set_ballspeed(1200.0f);
    if (level == 14) Ball->set_ballspeed(1250.0f);
    if (level == 15) Ball->set_ballspeed(1350.0f);
}

void Game::display_endgame()
{
    Endgame = new endgame(renderer);
    Endgame->Update(username,score,win);
    while(1)
    {
        SDL_RenderClear(renderer);
        Endgame->Render();
        SDL_RenderPresent(renderer);
        SDL_Event e;
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) break;
            if (e.type == SDL_KEYDOWN) break;
        }
    }
    delete Endgame;
}

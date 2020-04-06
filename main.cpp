#include <iostream>
#include "game.h"

int main(int argc,char* argv[])
{
    Game* game = new Game();
    if (game->Init())
    {
        if (game->loadgame())
        {
            if(game->getnameuser())
            {
                game->Run();
                game->display_endgame();
            }
        }
    }
    delete game;

    //info
    std::cout << "Breakout Game" << std::endl;
    std::cout << "Designed by: Nam Phan" << std::endl;
    std::cout << "University of Engineering and Technology" << std::endl;
    return 0;

}

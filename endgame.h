#ifndef ENDGAME_H_INCLUDED
#define ENDGAME_H_INCLUDED

#include "base.h"
#include <string>
#include <SDL_ttf.h>

using namespace std;

class endgame : public base
{
private:
    SDL_Texture* win_screen;
    SDL_Texture* lose_screen;
    string username;
    int score;
    bool win;
    TTF_Font* font;
    TTF_Font* font2;
    SDL_Color textColor;
public:
    endgame(SDL_Renderer* renderer);
    ~endgame();
    void Render();
    void Update(string username,int score,bool win);
};

#endif // ENDGAME_H_INCLUDED

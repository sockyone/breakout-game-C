#ifndef GETNAME_H_INCLUDED
#define GETNAME_H_INCLUDED

#include "base.h"
#include <string>
#include <SDL_ttf.h>

using namespace std;

class getname : public base
{
private:
    SDL_Texture* text2ture;
    string inputText;
    TTF_Font* font;
    SDL_Color textColor;
public:
    getname(SDL_Renderer* renderer);
    ~getname();
    string get_user_name();
    void Render();
    bool Update(bool &state);
};

#endif // GETNAME_H_INCLUDED

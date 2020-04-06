#include "getname.h"

getname::getname(SDL_Renderer* renderer) : base(renderer)
{
    SDL_Surface* surface_temp = SDL_LoadBMP("loadname.bmp");
    text2ture = SDL_CreateTextureFromSurface(renderer,surface_temp);
    SDL_FreeSurface(surface_temp);

    textColor={255,0,0};

    x = 100;
    y = 190;
    width = 35;
    height = 100;
    inputText="";
    font = TTF_OpenFont("myfont.ttf",36);
    SDL_StartTextInput();
}

getname::~getname()
{
    SDL_StopTextInput();
    SDL_DestroyTexture(text2ture);
    text2ture=NULL;
}

bool getname::Update(bool &state)
{
    bool quit_ = false;
    SDL_Event e;
    if (SDL_PollEvent( &e ) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            quit_ = true;
            state = false;
        }
        else if( e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
        {
            inputText.pop_back();
        }
        else if (e.type == SDL_TEXTINPUT)
        {
            if (inputText.length() < 25)
                inputText += e.text.text;
        }
        else if (e.key.keysym.sym == SDLK_RETURN && inputText.length()>0)
        {
            quit_ = true;
            state = true;
        }

    }

    return quit_;
}

void getname::Render()
{
    SDL_Rect temp1;
    temp1.x=0;
    temp1.y=0;
    temp1.w=1100;
    temp1.h=600;
    SDL_RenderCopy(renderer,text2ture,NULL,&temp1);

    SDL_Rect temp2;
    temp2.x = (int)x;
    temp2.y = (int)y;
    temp2.w = width*(inputText.length());
    temp2.h = height;
    SDL_Surface* text_Surface = TTF_RenderText_Solid(this->font, inputText.c_str(),textColor);
    SDL_Texture* text_Texture = SDL_CreateTextureFromSurface(renderer,text_Surface);
    SDL_FreeSurface(text_Surface);
    SDL_RenderCopy(renderer,text_Texture,NULL,&temp2);
    SDL_DestroyTexture(text_Texture);
}

string getname::get_user_name()
{
    string temp = inputText;
    int i = inputText.length();
    while (inputText[i-1] == ' ' && i>=0)
    {
        temp.pop_back();
        i--;
    }
    return temp;
}

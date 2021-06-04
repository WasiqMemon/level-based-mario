#include<iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#pragma once


using namespace std;


class Text{
    TTF_Font* font;
    SDL_Surface* surfaceMessage; 
    SDL_Texture* Message; 
    SDL_Rect Message_rect; //create a rect
public:
    Text(SDL_Rect);
    void draw(SDL_Renderer*, const char*);
};
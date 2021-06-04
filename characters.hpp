#include "SDL.h"
#pragma once
class Characters{
    protected:
    SDL_Renderer* gRenderer; //Pointer to renderer
    SDL_Texture* assets; //Pointer to image
    SDL_Rect onimage; //Rectangle on image
    SDL_Rect onwindow; //Rectangle on window
    public: 
    Characters(SDL_Renderer*, SDL_Texture*);
    void draw(SDL_RendererFlip, double); //Draws object with given flip
    SDL_Rect getMover(); //Return Mover
    ~Characters();
};
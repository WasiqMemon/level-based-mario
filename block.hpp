#include "SDL.h"
#include <iostream>
#pragma once
class Block{
protected:
    SDL_Texture* assets; //Pointer to image
    SDL_Rect src; //Rectangle on image
    SDL_Rect mover; //Rectangle on window
public:
    Block(SDL_Texture*);
    Block(SDL_Texture*, SDL_Rect);
    virtual void draw(SDL_Renderer*); //Draw the object (virtual function called by child classes only)
    virtual char onTouch(); //React to collision with mario
    SDL_Rect getMover(); //Return mover
    virtual ~Block(); //Reset all pointers
};
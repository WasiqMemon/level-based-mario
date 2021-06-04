#pragma once
#include "characters.hpp"

class Enemy: public Characters{
    protected:
    SDL_RendererFlip flip;  //flipping when changing direction
    int initx; //initial x coordinate
    
    public:  
    Enemy(SDL_Renderer*, SDL_Texture*);
    // virtual void draw();
    void move(); //Creates horizontal movement that loops and start at starting position of enemy
};

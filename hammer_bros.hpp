#pragma once
#include "enemy.hpp"

class Hammer: public Enemy{ //Does not do damage, but pushes you away
    SDL_Rect onimage[3]; // to make animation
    int frame;          // frame to be currently displayed for animation

public:
    Hammer(SDL_Renderer*, SDL_Texture*, SDL_Rect);
    void draw(); //Draws and moves hammer
    ~Hammer();
};
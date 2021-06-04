#pragma once
#include "enemy.hpp"

class Spiny: public Enemy{ //Damage no matter where you touch them
    SDL_Rect onimage[2]; // to make animation
    int frame;          // frame to be currently displayed for animation
    public:
    Spiny(SDL_Renderer*, SDL_Texture*, SDL_Rect);
    void draw(); //draw spiny
};
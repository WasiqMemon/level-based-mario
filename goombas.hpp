#pragma once
#include "enemy.hpp"

class Goomba: public Enemy{ //Can be killed from jumping on them. Damage when touched from sides.
    SDL_Rect onimage[2]; // to make animation
    int frame;          // frame to be currently displayed for animation
public:
    Goomba(SDL_Renderer*, SDL_Texture*, SDL_Rect);
    void draw(); //Draws and moves goomba
};
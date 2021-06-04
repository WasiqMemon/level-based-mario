#include "block.hpp"
#include <iostream>
#pragma once

class Brick: public Block {
    public:
    Brick(SDL_Texture*);
    Brick(SDL_Texture*, SDL_Rect);
    void draw(SDL_Renderer*); //Calls block's draw function
    char onTouch(); //Does nothing
    ~Brick();
};
#include "block.hpp"
#include <iostream>
#pragma once

class Coin: public Block {
    public:
    Coin(SDL_Texture*);
    Coin(SDL_Texture*, SDL_Rect);
    void draw(SDL_Renderer*); //Draw coin
    ~Coin();
};
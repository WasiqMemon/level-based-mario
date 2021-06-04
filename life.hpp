#include "SDL.h"
#include "block.hpp"
#include "text.hpp"
#include <list>
#pragma once

class Life: public Block{
    SDL_Rect live_mover[3]; //Position of each heart
    int count = 3; //Initial number of lives

public:
    Life(SDL_Texture*);
    void draw(SDL_Renderer*);
    Life& operator -- (int); //Decrement count when life object decrement
    void operator = (const int&); //Assign integer value to count
    bool below0(); //Check if life has become 0
    int getCount(); //Get number of lives
};
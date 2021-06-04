#include "block.hpp"
#include <iostream>
#pragma once

class ItemBlock: public Block { //A block that produces an item (coin) when hit from bottom
    public:
    ItemBlock(SDL_Texture*);
    ItemBlock(SDL_Texture*, SDL_Rect);
    void draw(SDL_Renderer*); //Draw itemBlock
    char onTouch(); //React to being hit
    ~ItemBlock();
};
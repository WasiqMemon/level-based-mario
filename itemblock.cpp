#include "itemblock.hpp"
#pragma once

ItemBlock::ItemBlock(SDL_Texture* texture): Block(texture) {}

ItemBlock::ItemBlock(SDL_Texture* tex, SDL_Rect initMover): Block(tex, initMover){}

void ItemBlock::draw(SDL_Renderer* renderer) {
    Block::draw(renderer);
}

char ItemBlock::onTouch() {
    if (src.x == 0) { //Check if in initial state
        src.x = 32; //Set to used state
        return 'c'; //Tell its caller to produce a coin
    }
    return ' ';//Do nothing
}

ItemBlock::~ItemBlock() {};
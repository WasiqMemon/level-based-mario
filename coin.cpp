#include "coin.hpp"
#pragma once

Coin::Coin(SDL_Texture* texture): Block(texture) {
    src = {0, 0, 800, 800};
    mover = {0, 0, 32, 32};
}

Coin::Coin(SDL_Texture* tex, SDL_Rect initMover): Coin(tex){
    mover.x = initMover.x;
    mover.y = initMover.y;
}

void Coin::draw(SDL_Renderer* renderer) {
    Block::draw(renderer);
}

Coin::~Coin() {};
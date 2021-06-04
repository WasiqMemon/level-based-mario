#include "brick.hpp"
#pragma once

Brick::Brick(SDL_Texture* texture): Block(texture) {}

Brick::Brick(SDL_Texture* tex, SDL_Rect initMover): Block(tex, initMover){}

void Brick::draw(SDL_Renderer* renderer) {
    Block::draw(renderer);
}

char Brick::onTouch() {return ' ';}; //Space char means no action on touch

Brick::~Brick() {};
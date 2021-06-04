#include "spiny.hpp"
#include <iostream>

using namespace std;

Spiny::Spiny(SDL_Renderer* renderer, SDL_Texture* asset, SDL_Rect mover): Enemy(renderer, asset)
{
    flip = SDL_FLIP_NONE;
    frame = 0;
    onimage[0] = {451, 763, 16, 15};
    onimage[1] = {472, 762, 16, 16};
    onwindow = mover;
    initx = mover.x;
}

void Spiny::draw(){
    Enemy::move();
    if (frame < 19) frame++;
    else frame = 0;
    Characters::onimage = onimage[frame/10];
    Characters::draw(flip, 0);
}
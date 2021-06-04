#include "hammer_bros.hpp"
#include <iostream>

using namespace std;

Hammer::Hammer(SDL_Renderer* renderer, SDL_Texture* asset, SDL_Rect m): Enemy(renderer, asset)
{
    frame = 0;
    onimage[0] = {424, 945, 15, 24};
    onimage[1] = {444, 945, 16, 24};
    onimage[2] = {466, 945, 16, 24};
    onwindow = m;
    gRenderer = renderer;
    assets = asset;
    initx = m.x;
}

void Hammer::draw(){
    Enemy::move();
    if (frame < 29) frame++;
    else frame = 0;
    Characters::onimage = onimage[frame/10];
    Characters::draw(flip, 0);
}

Hammer::~Hammer(){}
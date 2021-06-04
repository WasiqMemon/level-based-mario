#include "goombas.hpp"
#include <iostream>

using namespace std;

Goomba::Goomba(SDL_Renderer* renderer, SDL_Texture* asset, SDL_Rect mover): Enemy(renderer, asset)
{
    frame = 0;
    onimage[0] = {187, 894, 16, 16};
    onimage[1] = {208, 894, 16, 16};
    onwindow = mover;
    initx = mover.x;
}

void Goomba::draw(){
    move();
    if (frame < 19) frame++;
    else frame = 0;
    Characters::onimage = onimage[frame/10];
    Characters::draw(flip, 0);
}
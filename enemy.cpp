#include "enemy.hpp"
#include <iostream>

using namespace std;

Enemy::Enemy(SDL_Renderer* renderer, SDL_Texture* asst): Characters(renderer, asst){
    flip = SDL_FLIP_NONE;
    initx = 0;
};

void Enemy::move()
{
    if (flip == SDL_FLIP_HORIZONTAL) { //Check if enemy is going right
        if (onwindow.x < initx + 64) {
            onwindow.x ++;
        }
        else {
            flip = SDL_FLIP_NONE; //Make the enemy face left if it has reached the max right point
        }
    }
    else { //If enemy is going left
        if (onwindow.x > initx) {
            onwindow.x --;
        }
        else {
            flip = SDL_FLIP_HORIZONTAL; //Make the enemy face right if it has reached the max left point
        }
    }
}


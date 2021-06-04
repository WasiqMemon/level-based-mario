#include<iostream>
#include"mario.hpp"

using namespace std;

Mario::Mario(SDL_Renderer* renderer, SDL_Texture* asset, Level* curr): Characters(renderer, asset)
{
    flip = SDL_FLIP_NONE;
    currLevel = curr;
    frame = 50;
    onimage[0] = {1, 0, 16, 16};
    onimage[1] = {33, 0, 16, 16};
    onimage[2] = {62, 0, 16, 16};
    onimage[3] = {89, 0, 16, 16};
    onimage[4] = {123, 0, 16, 16};
    onimage[5] = {151, 0, 16, 16};
    onwindow = {128, 272, 32, 32};
    falling = true;
    jumping = false;
}

Mario* Mario::getMario(SDL_Renderer* renderer, SDL_Texture* asset, Level* curr) {
    if (mario == nullptr) {
        mario = new Mario(renderer, asset, curr);
        return mario;
    }
    return mario;
}

void Mario::move()
{
    if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_A]) {
        if (state[SDL_SCANCODE_D]) {
            flip = SDL_FLIP_NONE;
            char collResult = currLevel->rightCollCheck(onwindow);
            if (collResult == 'm'){ // m = can move
                onwindow.x += 1;
            }
            if (collResult == 'n'){ // n = new level
                onwindow.x=0; //Bring mario to left
            }
            if (collResult == 'd'){ // d = taken damage, so move back
                onwindow.x-=16;
            }
        }
        else if (state[SDL_SCANCODE_A]) {
            flip = SDL_FLIP_HORIZONTAL;
            char collResult = currLevel->leftCollCheck(onwindow);
            if (collResult != 'b'){ // b = blocked
                onwindow.x += -1;
            }
            if (collResult == 'p'){ // p = previous level
                onwindow.x=800-32; //Bring mario to right
            }
            if (collResult == 'd'){
                onwindow.x+=16;
            }
        }
        if (!jumping && !falling) { //If walking animation if not jumping or falling
            frame++;
            if (frame > 29) {
                frame = 0;
            }
        }
    }
    else {
        if (!jumping && !falling) { //Jumping/Falling sprite when these states are true
            frame = 0;
        }
    }
}

void Mario::fall() {
    if (!falling) {
        char collResult = currLevel->downCollCheck(onwindow); 
        if (collResult != 'b' && !jumping) { //Nothing below and not going up
            falling = true;
            frame = 50;
        }
    }
    if (falling) {
        onwindow.y += 1;
        char collResult = currLevel->downCollCheck(onwindow);
        if (collResult == 'b') {
            falling = false;
            frame = 0;
        }
        else if (collResult == 'j') { // j = jump; after hitting goomba or hammer from top
            falling = false;
            jumping = true;
            jumpHeight = onwindow.y - 34;
            frame = 50;
        }
    }
}

void Mario::jump() {
    if (!jumping) {
        if (state[SDL_SCANCODE_W] && !falling) {
            jumping = true;
            jumpHeight = onwindow.y - 66;
            frame = 50;
        }
    }
    if (jumping) {
        if (currLevel->upCollCheck(onwindow) != 'b' && onwindow.y > jumpHeight) { //come back down when jumpheight reached or blocked from top
            onwindow.y -= 2;
        }
        else {
            jumping = false;
        }
    }
}

void Mario::draw()
{
    move();
    fall();
    jump();
    Characters::onimage = onimage[frame/10];
    Characters::draw(flip, 0);
}

Mario* Mario::mario = nullptr; 

void Mario::resetMario() { //Reset static mario pointer
    delete mario;
    mario = nullptr;
}

Mario::~Mario() {
    currLevel = nullptr;
    state = nullptr;
}
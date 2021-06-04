#include<iostream>
#include"characters.hpp"

Characters::Characters(SDL_Renderer* renderer, SDL_Texture* asset): gRenderer(renderer), assets(asset){}

void Characters::draw(SDL_RendererFlip flip, double angle) {
    SDL_RenderCopyEx(gRenderer, assets, &onimage, &onwindow, angle, NULL, flip);
}

SDL_Rect Characters::getMover() {return onwindow;}

Characters::~Characters() {
    gRenderer = nullptr;
    assets = nullptr;
}
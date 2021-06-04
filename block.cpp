#include "block.hpp"

Block::Block(SDL_Texture* texture) {
    //Initialize image and size
    assets = texture;
    src = {0, 0, 32, 32};
    mover = {0, 0, 32, 32};
}

Block::Block(SDL_Texture* tex, SDL_Rect initMover): Block(tex) {
    //Initialize position
    mover.x = initMover.x;
    mover.y = initMover.y;
}

void Block::draw(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, assets, &src, &mover);
}

char Block::onTouch() {}

SDL_Rect Block::getMover() { //get SDLRect of an object's mover 
    return mover;
}

Block::~Block() {
    assets = nullptr;
};
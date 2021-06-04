#include<iostream>
#include "text.hpp"


Text::Text(SDL_Rect mover): Message_rect(mover) {
    font = TTF_OpenFont(".\\fonts\\mario.ttf", 18);
    if(!font) {
        std::cout <<TTF_GetError();   // handle error
    }
}

void Text::draw(SDL_Renderer* renderer, const char* content){
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, content, {255, 255, 255}); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //render text

    //Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}
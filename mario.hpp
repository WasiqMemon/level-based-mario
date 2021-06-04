#pragma once
#include "characters.hpp"
#include "level.hpp"
class Mario: public Characters{
    SDL_RendererFlip flip;  //flipping when changing direction
    int frame;          // frame to be currently displayed for animation
    Level* currLevel;
    SDL_Rect onimage[6]; // to make animation
    const Uint8 *state = SDL_GetKeyboardState(NULL); //To read keyinput
    int jumpHeight; //For coming down after jumping
    bool falling; //Is mario falling?
    bool jumping; //Is mario in the middle of a jump?
    Mario(SDL_Renderer*, SDL_Texture*, Level*);
    static Mario* mario; //To make class singleton
public:  
    static Mario* getMario(SDL_Renderer*, SDL_Texture*, Level*);
    static void resetMario();
    void draw(); //Draw mario and handle movement
    void move(); //Move mario based on input from keys {A = left, D = Right}
    void fall(); //Make mario fall if nothing below him
    void jump(); //Jump when W pressed
    ~Mario();
};

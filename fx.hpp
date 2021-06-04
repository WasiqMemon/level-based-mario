#pragma once
#include <SDL.h>
#include <SDL_mixer.h>

class FX{ //Handles sounds effects for collisions
    Mix_Chunk *jump = NULL;
    Mix_Chunk *touch = NULL;
    Mix_Chunk *stomp = NULL;
    Mix_Chunk *coin = NULL;

public:
    void initialize(); //Initialize sound
    void load(); //Load all sounds from music folder
    void destroy(); //Free the sounds
    void effect(char); //Play sounds correlating to given char
};
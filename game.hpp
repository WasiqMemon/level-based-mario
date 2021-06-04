#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <list>
#include "mario.hpp"

using namespace std;

class Game{
    const int SCREEN_WIDTH = 800; //Screen width
    const int SCREEN_HEIGHT = 400; //Screen height
    SDL_Window* gWindow = NULL; //SDL window that will display the game
    SDL_Renderer* gRenderer = NULL; //SDL Renderer to display objects
    SDL_Texture* gTextures[3] = {NULL, NULL, NULL}; //Background textures: 3 for each level
    SDL_Texture* startTexture = NULL; //Texture for startscreen
    SDL_Texture* endTexture = NULL; //Texture for endscreen
    SDL_Texture* wonTexture = NULL; //Texture for winscreen
    SDL_Texture* assets[5] = {NULL, NULL, NULL}; //Sprites images for blocks, and third image for the remaining assets 
    SDL_Texture* mario_img=NULL; //Sprites of Mario
    Mix_Music *bgMusic = NULL; //Background Music
    Mix_Chunk *die = NULL; //dying sound
    string gameState = "start"; //[start = start screen, newgame = load new level, loadgame = load level data from save, playing = game running, end = lost, won, endwaiting and wonwaiting when waiting for keypress]
    Mario* mario; //Mario object
    Level* level; //Level to be played
public:
    bool init(); //Initialize SDL Objects and gamestate variable
    bool loadMedia(); //Load all media
    void close(); //Acts like a deconstructor
    SDL_Texture* loadTexture( std::string path ); //Loads textures and returns their pointers
    void run(); // Run the game
    void drawAllObjects(); // Draws all objects
};


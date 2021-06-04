#include "SDL.h"
#include "brick.hpp"
#include "itemblock.hpp"
#include "spiny.hpp"
#include "hammer_bros.hpp"
#include "goombas.hpp"
#include <list>
#include <string>
#include <fstream>
#include <vector>
#include "factory.hpp"
#include "coin.hpp"
#include "life.hpp"
#include "fx.hpp"
#include "text.hpp"
#pragma once

using namespace std;
class LevelPart {
    //Lists of pointers of all objects to be displayed
    list<Block*> blocks;
    list<Spiny*> spiny;
    list<Hammer*> hammers;
    list<Goomba*> goombas;
    list<Coin*> coins;
    Life* life; //Points to life object from Level class
    int* coinsCount; //Points to coins count from Level class
    SDL_Texture* coin_img; //Points to coin image for coin generation
    FX sound; //Used to play sounds
    Text* coinsDisplay; //Displays how many coins
    void create(string, SDL_Renderer*, SDL_Texture**); //Load the data from file into lists using Factory class
    public:
    LevelPart(string, SDL_Renderer*, SDL_Texture**, Life*, int*);
    void display(SDL_Renderer*); //Dispalys everything
    char rightCollCheck(SDL_Rect); //Checks collision of each object with mario for each side
    char leftCollCheck(SDL_Rect);
    char downCollCheck(SDL_Rect);
    char upCollCheck(SDL_Rect);
    ~LevelPart();
};
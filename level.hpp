#include "levelpart.hpp"

class Level {
    list<LevelPart*> parts; // List of levelparts pointers for each part that will be loaded
    list<LevelPart*>::iterator currPart; //Iterator of the part currently being displayed
    SDL_Texture* *bgs; //Array of backgrounds (1 for each of the 3 levels)
    int noOfLevels = 6; //Number of level parts
    int currLvl; //Current level (0,1 or 2)
    int currLvlPart; //Current part of the current level (0 or 1)
    Life* life; //Mario's life
    int* coins; //Coins collected
    bool won; //True if mario reached end
    public:
    Level(SDL_Renderer*, SDL_Texture**, SDL_Texture**, int);
    Level(SDL_Renderer*, SDL_Texture**, SDL_Texture**, int, int, int);
    void loadLevel(string, SDL_Renderer*, SDL_Texture**); //Loads data from level.txt files into the levelparts array, one object for each file
    void display(SDL_Renderer*); //Display current levelpart
    char rightCollCheck(SDL_Rect); //Check collisio at Mario's right
    char leftCollCheck(SDL_Rect); //Check collisio at Mario's left
    char downCollCheck(SDL_Rect); //Check collisio at Mario's bottom
    char upCollCheck(SDL_Rect); //Check collisio at Mario's top
    bool isMarioDead(); //Check if 0 lives left
    bool hasGameWon(); //Check if won has become true
    void save(); //Saves current level, lives and coins in separate lines into savegame.txt
    ~Level();
};
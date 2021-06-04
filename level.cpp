#include "level.hpp"

Level::Level(SDL_Renderer* renderer, SDL_Texture* assets[], SDL_Texture* bg[], int lvl) {
    bgs = bg; //Pointing to backgrounds
    won = false; //Game not won
    currLvl = lvl-1; //Current level based on level passed (-1 because used as array index)
    currLvlPart = 0; //First part
    life = new Life(assets[4]);
    coins = new int(0); // 0 coins
    loadLevel("level", renderer, assets);
    currPart = parts.begin(); //Start of level
    printf(to_string(currLvlPart).c_str());
}

Level::Level(SDL_Renderer* renderer, SDL_Texture* assets[], SDL_Texture* bg[], int lvl, int lives, int coinsCount): Level(renderer, assets, bg, lvl) {
    //Level created with given data for coins and lives
    (*coins) = coinsCount;
    (*life) = lives;
}

void Level::loadLevel(string lvlName, SDL_Renderer* renderer, SDL_Texture* assets[]) {
    //Load current level and all further levels from files (previus levels not loaded in case of load game to save space)
    for (int i = currLvl*2; i<noOfLevels; i++) {
        parts.push_back(new LevelPart(".\\levels\\"+lvlName+"_"+to_string(i+1)+".txt", renderer, assets, life, coins));
    }
}
void Level::display(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, bgs[currLvl], NULL, NULL); //Display background based on currlvl
    (*currPart)->display(renderer); //Display the currlvl
}
char Level::rightCollCheck(SDL_Rect marioMover) {
    if (marioMover.x+32 == 799) {
        printf(to_string(currLvlPart).c_str());
        if (currLvlPart == 1 && currLvl != 2) { //Moving to next level
            currPart++;
            currLvlPart = 0;
            currLvl++;
            save(); //Save only when new level
            return 'n';
        }
        else if (currLvlPart == 0) { //Moving to mext part of same level
            currPart++;
            currLvlPart++;
            return 'n';
        }
        won = true; //Very end reached, hence game won
        return 'b';
    }
    return (*currPart)->rightCollCheck(marioMover);
}
char Level::leftCollCheck(SDL_Rect marioMover) {
    if (marioMover.x >= -1 && marioMover.x < 1) { //Prevent Mario from falling out of window
        if (currLvlPart == 0) {
            return 'b';
        }
        currPart--;
        currLvlPart--;
        return 'p';
    }
    return (*currPart)->leftCollCheck(marioMover);
}
char Level::downCollCheck(SDL_Rect marioMover) {
    return (*currPart)->downCollCheck(marioMover);
}
char Level::upCollCheck(SDL_Rect marioMover) {
    return (*currPart)->upCollCheck(marioMover);
}
bool Level::isMarioDead() {
    return life->below0();
}
bool Level::hasGameWon() {
    return won;
}
Level::~Level() {
    printf("deleting levelparts\n");
    while(!parts.empty()) delete parts.front(), parts.pop_front(); // relieve all level parts; code taken from https://stackoverflow.com/questions/307082/cleaning-up-an-stl-list-vector-of-pointers
    delete life;
    delete coins;
    coins = nullptr;
    life = nullptr;
    bgs = nullptr;
    printf("done deleting levelpartS\n");
}
void Level::save() {
    ofstream saveFile(".\\levels\\savegame.txt");
    saveFile << currLvl+1 << endl;
    saveFile << life->getCount() << endl;
    saveFile << *coins << endl;
    saveFile.close();
}
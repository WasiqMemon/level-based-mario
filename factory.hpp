#include "brick.hpp"
#include "itemblock.hpp"
#include "spiny.hpp"
#include "hammer_bros.hpp"
#include "goombas.hpp"
#include <string>
#include <vector>
#include <list>

using namespace std;

class Factory { //Generates lists of each enemy and block to be displayed based on data from file
    vector<string> parseData (string);
    list<Block*> blocks;
    list<Spiny*> spiny;
    list<Hammer*> hammers;
    list<Goomba*> goombas;
    public:
    Factory();
    void makeObject(string, SDL_Renderer*, SDL_Texture**);
    list<Block*> getBlocks();
    list<Spiny*> getSpiny();
    list<Hammer*> getHammers();
    list<Goomba*> getGoombas();
};
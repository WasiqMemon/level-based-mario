#include "levelpart.hpp"

using namespace std;

LevelPart::LevelPart (string filename, SDL_Renderer* renderer, SDL_Texture* image[], Life* l, int* c) {
    coinsDisplay = new Text({336, 16, 128, 18});
    coin_img = image[3];
    life = l;
    coinsCount = c;
    create(filename, renderer, image);
    sound.initialize();
    sound.load();
} 

void LevelPart::create (string filename, SDL_Renderer* renderer, SDL_Texture* blAssets[]) {
    int i = 1;
    ifstream dataFile(filename);
    string data;
    Factory newFactory;    
    while (getline(dataFile, data)) {
        newFactory.makeObject(data, renderer, blAssets);
    }
    blocks = newFactory.getBlocks();
    spiny = newFactory.getSpiny();
    goombas = newFactory.getGoombas();
    hammers = newFactory.getHammers();
}

void LevelPart::display(SDL_Renderer* renderer) {
    for (auto i: blocks) {
        i->draw(renderer);
    }
    for (auto i: spiny) {
        i->draw();
    }
    for (auto i: hammers) {
        i->draw();
    }
    for (auto i: goombas) {
        i->draw();
    }
    for (auto i: coins) {
        i->draw(renderer);
    }
    life->draw(renderer);
    string coinStr = "Coins "+to_string(*coinsCount);
    coinsDisplay->draw(renderer, coinStr.c_str());
}

char LevelPart::rightCollCheck(SDL_Rect marioMover) {
    // Check blocks
    for (auto i: blocks) {
        auto blockMover = i->getMover();
        if (marioMover.x+32 >= blockMover.x && marioMover.x+32 < blockMover.x+2 && marioMover.y >= blockMover.y-32 && marioMover.y < blockMover.y+32) {
            return 'b';
        }
    }
    //Check coins
    for (auto it = coins.cbegin(); it!=coins.end(); it++) {
        auto blockMover = (*it)->getMover();
        if (marioMover.x+32 >= blockMover.x && marioMover.x+32 < blockMover.x+2 && marioMover.y >= blockMover.y-32 && marioMover.y < blockMover.y+32) {
            //Coin is deleted and coin count is increased
            delete(*it);
            coins.erase(it--);
            sound.effect('c');
            (*coinsCount)++;
            return 'm';
        }
    }
    // Check with each enemy
    for (auto i: goombas) {
        auto goombaMover = i->getMover();
        if (marioMover.x+32 >= goombaMover.x && marioMover.x+32 < goombaMover.x+2 && marioMover.y >= goombaMover.y-32 && marioMover.y < goombaMover.y+32) {
            sound.effect('s');
            (*life)--; //Life lost
            return 'd';
        }
    }
    for (auto i: spiny) {
        auto spinyMover = i->getMover();
        if (marioMover.x+32 >= spinyMover.x && marioMover.x+32 < spinyMover.x+2 && marioMover.y >= spinyMover.y-32 && marioMover.y < spinyMover.y+32) {
            sound.effect('s');
            (*life)--; //Life lost
            return 'd'; 
        }
    }
    for (auto i: hammers) {
        auto hammerMover = i->getMover();
        if (marioMover.x+32 >= hammerMover.x && marioMover.x+32 < hammerMover.x+2 && marioMover.y >= hammerMover.y-32 && marioMover.y < hammerMover.y+32) {
            return 'd';
        }
    }
    return 'm';
}

char LevelPart::leftCollCheck(SDL_Rect marioMover) {
    //Similar ro rightCollCheck
    for (auto i: blocks) {
        auto blockMover = i->getMover();
        if (marioMover.x >= blockMover.x+32 && marioMover.x < blockMover.x+34 && marioMover.y >= blockMover.y-32 && marioMover.y < blockMover.y+32) {
            return 'b';
        }
    }
    for (auto it = coins.cbegin(); it!=coins.end(); it++) {
        auto blockMover = (*it)->getMover();
        if (marioMover.x >= blockMover.x+32 && marioMover.x < blockMover.x+34 && marioMover.y >= blockMover.y-32 && marioMover.y < blockMover.y+32) {
            delete(*it);
            coins.erase(it--);
            sound.effect('c');
            (*coinsCount)++;
            return 'm';
        }
    }
    for (auto i: goombas) {
        auto goombaMover = i->getMover();
        if (marioMover.x >= goombaMover.x+32 && marioMover.x < goombaMover.x+34 && marioMover.y >= goombaMover.y-32 && marioMover.y < goombaMover.y+32) {
            sound.effect('d');
            (*life)--;
            return 'd';
        }
    }
    for (auto i: spiny) {
        auto spinyMover = i->getMover();
        if (marioMover.x >= spinyMover.x+32 && marioMover.x < spinyMover.x+34 && marioMover.y >= spinyMover.y-32 && marioMover.y < spinyMover.y+32) {
            sound.effect('d');
            (*life)--;
            return 'd';
        }
    }
    for (auto i: hammers) {
        auto hammerMover = i->getMover();
        if (marioMover.x >= hammerMover.x+32 && marioMover.x < hammerMover.x+34 && marioMover.y >= hammerMover.y-32 && marioMover.y < hammerMover.y+32) {
            return 'd';
        }
    }
    return 'm';
}

char LevelPart::downCollCheck(SDL_Rect marioMover) {
    //Similar ro rightCollCheck
    if (marioMover.y+32 >= 336 && marioMover.y+32 < 340) {
        return 'b';
    }
    for (auto i: blocks) {
        auto blockMover = i->getMover();
        if (marioMover.y+32 >= blockMover.y-1 && marioMover.y+32 < blockMover.y+2 && marioMover.x >= blockMover.x-30 && marioMover.x < blockMover.x+32) {
            return 'b';
        }
    }
    for (auto it = coins.cbegin(); it!=coins.end(); it++) {
        auto blockMover = (*it)->getMover();
        if (marioMover.y+32 >= blockMover.y-1 && marioMover.y+32 < blockMover.y+2 && marioMover.x >= blockMover.x-30 && marioMover.x < blockMover.x+32) {
            delete(*it);
            coins.erase(it--);
            sound.effect('c');
            (*coinsCount)++;
            return 'm';
        }
    }
    for (auto it = goombas.cbegin(); it!=goombas.end(); it++) {
        auto goombaMover = (*it)->getMover();
        if (marioMover.y+32 >= goombaMover.y-1 && marioMover.y+32 < goombaMover.y+2 && marioMover.x >= goombaMover.x-30 && marioMover.x < goombaMover.x+32) {
            //Kill goomba
            delete(*it);
            goombas.erase(it--);
            sound.effect('s');
            return 'j';
        }
    }
    for (auto it = spiny.cbegin(); it!=spiny.end(); it++) {
        auto spinyMover = (*it)->getMover();
        if (marioMover.y+32 >= spinyMover.y-1 && marioMover.y+32 < spinyMover.y+2 && marioMover.x >= spinyMover.x-30 && marioMover.x < spinyMover.x+32) {
            sound.effect('s');
            (*life)--;
            return 'j';
        }
    }
    for (auto it = hammers.cbegin(); it!=hammers.end(); it++) {
        auto hammerMover = (*it)->getMover();
        if (marioMover.y+32 >= hammerMover.y-1 && marioMover.y+32 < hammerMover.y+2 && marioMover.x >= hammerMover.x-30 && marioMover.x < hammerMover.x+32) {
            sound.effect('j');
            return 'j';
        }
    }
    return 'm';
}

char LevelPart::upCollCheck(SDL_Rect marioMover) {
    if (marioMover.y+32 >= 0 && marioMover.y+32 < 4) {
        return 'b';
    }
    char touchReturn;
    for (auto i: blocks) {
        auto blockMover = i->getMover();
        if (marioMover.y >= blockMover.y+31 && marioMover.y < blockMover.y+33 && marioMover.x >= blockMover.x-30 && marioMover.x < blockMover.x+32) {
            touchReturn = i->onTouch(); //Update block
            if (touchReturn == 'c') { //Produce coin on top of block if block returns c
                coins.push_back(new Coin(coin_img, {blockMover.x, blockMover.y - 32, 32, 32}));
                sound.effect('t');
            }
            return 'b';
        }
    }
    return 'm';
}

LevelPart::~LevelPart() {
    printf("deleting levelpart\n");
    sound.destroy();
    life = nullptr;
    coinsCount = nullptr;
    coin_img = nullptr;
    while(!blocks.empty()) delete blocks.front(), blocks.pop_front(); 
    while(!spiny.empty()) delete spiny.front(), spiny.pop_front(); 
    while(!hammers.empty()) delete hammers.front(), hammers.pop_front(); 
    while(!goombas.empty()) delete goombas.front(), goombas.pop_front(); 
    while(!coins.empty()) delete coins.front(), coins.pop_front(); 
}
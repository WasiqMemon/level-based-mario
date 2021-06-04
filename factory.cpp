#include "factory.hpp"

Factory::Factory() {};
vector<string> Factory::parseData (string data) { //Each line has data in format "objName <tab> xCoord <tab> yCoord"
    string curr = "";
    vector<string> parsedData;
    for (auto chr: data) {
        if (chr == '\t') {
            parsedData.push_back(curr);
            curr = "";
        }
        else {
            curr += chr;
        }
    }
    parsedData.push_back(curr);
    return parsedData;
}
void Factory::makeObject(string data, SDL_Renderer* renderer, SDL_Texture* blAssets[]) {
    vector<string> parsedData = parseData(data);
    if (parsedData.at(0) == "brick") {
        blocks.push_back(new Brick(blAssets[0], {stoi(parsedData.at(1))*32, stoi(parsedData.at(2))*32 + 16, 0, 0}));
    }
    if (parsedData.at(0) == "itemblock") {
        blocks.push_back(new ItemBlock(blAssets[1], {stoi(parsedData.at(1))*32, stoi(parsedData.at(2))*32 + 16, 0, 0}));
    }
    if (parsedData.at(0) == "spiny") {
        spiny.push_back(new Spiny(renderer, blAssets[2], {stoi(parsedData.at(1))*32, stoi(parsedData.at(2))*32 + 16, 32, 32}));
    }
    if (parsedData.at(0) == "hammer") {
        hammers.push_back(new Hammer(renderer, blAssets[2], {stoi(parsedData.at(1))*32, stoi(parsedData.at(2))*32 + 16, 32, 32}));
    }
    if (parsedData.at(0) == "goombas") {
        goombas.push_back(new Goomba(renderer, blAssets[2], {stoi(parsedData.at(1))*32, stoi(parsedData.at(2))*32 + 16, 32, 32}));
    }
}

list<Block*> Factory::getBlocks() {
    return blocks;
}
list<Spiny*> Factory::getSpiny() {
    return spiny;
}
list<Hammer*> Factory::getHammers() {
    return hammers;
}
list<Goomba*> Factory::getGoombas() {
    return goombas;
}


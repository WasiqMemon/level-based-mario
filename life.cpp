#include "life.hpp"
#include <iostream>

using namespace std;

Life::Life(SDL_Texture* tex): Block(tex)
{
    src = {0, 2, 20, 16};
}

void Life::draw(SDL_Renderer* renderer)
{
    for (int i = 0; i < count; i++)
    {
        mover = {15 + (i*30), 16, 20, 20};
        Block::draw(renderer);
        SDL_RenderCopy(renderer, assets, &src, &mover);
    }
}

Life& Life::operator--(int) {
    count--;
    return *this;
}
void Life::operator=(const int &i) {
    count = i;
}
bool Life::below0(){
    return count<=0;
}
int Life::getCount() {
    return count;
}
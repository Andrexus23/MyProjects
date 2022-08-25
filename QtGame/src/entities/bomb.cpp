#include "../../inc/entities/bomb.h"
#include "QDebug"
Bomb::Bomb(int x, int y):x(x), y(y){}

void Bomb::changeScore(Player *player) {
}

void Bomb::changeLives(Player *player) {
    if(!(player->dead())) player->minusHp();
    available = false;
}

CellStatus Bomb::getClass()
{
    return BOMB;
}

int Bomb::getX()
{
    return x;
}

int Bomb::getY()
{
    return y;
}

bool Bomb::isAvailable()
{
    return available;
}

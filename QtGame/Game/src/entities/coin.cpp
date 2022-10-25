#include "../../inc/entities/coin.h"

Coin::Coin(int x, int y):x(x), y(y){}

void Coin::changeScore(Player * player)
{
    player->addScore();
    available = false;
}

void Coin::changeLives(Player *player)
{

}

CellStatus Coin::getClass()
{
    return COIN;
}

int Coin::getX()
{
    return x;
}

int Coin::getY()
{
    return y;
}

bool Coin::isAvailable()
{
    return available;
}

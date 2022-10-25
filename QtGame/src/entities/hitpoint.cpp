#include "../../inc/entities/Hitpoint.h"
//#include "../../inc/cell.h"

void Hitpoint::changeScore(Player *player) {

}

void Hitpoint::changeLives(Player *player) {
    player->plusHp();
    available = false;
}

CellStatus Hitpoint::getClass()
{
    return HITPOINT;
}

int Hitpoint::getX()
{
    return x;
}

int Hitpoint::getY()
{
    return y;
}

bool Hitpoint::isAvailable()
{
    return available;
}

Hitpoint::Hitpoint(int x, int y):x(x), y(y) {}

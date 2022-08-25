#ifndef IELEMENT_H
#define IELEMENT_H
#include "player.h"

class IElement
{
public:
    virtual void changeLives(Player * player) = 0;
    virtual void changeScore(Player * player) = 0;
    virtual CellStatus getClass() = 0;
    virtual int getX() = 0;
    virtual int getY() = 0;
    virtual bool isAvailable() = 0;
    virtual ~IElement(){};
};

#endif // IELEMENT_H

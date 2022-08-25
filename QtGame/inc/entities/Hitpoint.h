#ifndef HITPOINT_H
#define HITPOINT_H
#include "ielement.h"
//#include "player.h"

class Hitpoint : public IElement
{
public:
    Hitpoint(int x=0, int y=0);
    void changeScore(Player * player) override;
    void changeLives(Player * player) override;
    CellStatus getClass() override;
    int getX() override;
    int getY() override;
    bool isAvailable() override;
private:
    bool available = true;
    int x = 0;
    int y = 0;
};
#endif // HITPOINT_H

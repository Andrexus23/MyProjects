#ifndef BOMB_H
#define BOMB_H

#include "ielement.h"
//#include "player.h"
#include "../../inc/allclasses.h"

class Bomb : public IElement{
public:
    Bomb(int x = 0, int y = 0);
    void changeScore(Player * player) override;
    void changeLives(Player * player) override;
    CellStatus getClass() override;
    int getX() override;
    int getY() override;
    bool isAvailable() override;
private:
    bool available = true;
    int x;
    int y;
};

#endif // BOMB_H

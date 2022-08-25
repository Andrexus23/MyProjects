#ifndef COIN_H
#define COIN_H
#include "ielement.h"

class Coin : public IElement
{
public:
    Coin(int x=0, int y=0);
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

#endif // COIN_H

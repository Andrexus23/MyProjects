#ifndef CELL_H
#define CELL_H
#include "iostream"
#include "algorithm"

#define CELLSIZE 40

using namespace std;



enum CellStatus{
    EMPTY,
    PLAYER,
    BOMB,
    COIN,
    HITPOINT,
    WALL,
    ENEMY
};

class Cell{
public:
    Cell(CellStatus argStatus);
    Cell(){};
    ~Cell(){};
    CellStatus & getStatus();
    CellStatus & getPrevStatus();
private:
    CellStatus status;
    CellStatus prevStatus;
};

#endif // CELL_H

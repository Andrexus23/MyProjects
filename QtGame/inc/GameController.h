#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "./entities/player.h"
#include "./entities/ielement.h"
#include "./entities/bomb.h"
#include "./entities/coin.h"
#include "./entities/Hitpoint.h"
#include "map.h"
#include "QWidget"
#include "QDebug"
#include "QKeyEvent"

class GameController:public QWidget {
    Q_OBJECT
public:
    GameController();
    ~GameController();
    IElement * deleteEntity(IElement * el);
    IElement * addEntity(IElement * el);
    void printEntities();
    CellStatus whatInCell(int x, int y);
    void moveUp();
    void moveDown();
    void moveRight();
    void moveLeft();
    void update();
    void generateMaze();
    void checkEntityCollision(int & newX, int & newY);
    void generateEntities(int nBombs, int nHits, int nCoins);
    bool someThingChanged();
    bool cellChanged(int x, int y);
    bool gameOver = false;
    Player * getPlayer();
private:
     Player * player;
     bool playerMoved = true;
     IElement ** entities;
     int sizeEntities;
     Map & map = Map::instance();

};

#endif // GAMECONTROLLER_H

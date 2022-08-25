#ifndef MAPVIEW_H
#define MAPVIEW_H
#include "QGraphicsScene"
#include "QGraphicsItem"
#include "../inc/map.h"
#include "../inc/GameController.h"


#define SCENEWIDTH 1240
#define SCENEHEIGHT 600
#define VIEWWIDTH 700

class MapView:public QGraphicsScene{
public:
    MapView(Map * map, GameController * gameController);
    ~MapView();
    QGraphicsItem * defineEntities(CellStatus  status);
    void drawMap();
private:
    Map * map;
    GameController * gameController;
    QGraphicsItem *** tiles;
    int mapHeight;
    int mapWidth;
    QPainter * painter;
    friend class Iterator;
};

#endif // MAPVIEW_H

#include "../inc/MapView.h"
#include "QDebug"
#include "QPainter"
#include "../inc/objectsView/PlayerGraphicsItem.h"
#include "../inc/objectsView/EmptyGraphicsItem.h"
#include "../inc/objectsView/CoinGraphicsItem.h"
#include "../inc/objectsView/BombGraphicsItem.h"
#include "../inc/objectsView/HitpointGraphicsItem.h"
#include "../inc/objectsView/WallGraphicsItem.h"

MapView::MapView(Map *map, GameController * gameController):map(map),  gameController(gameController){
        mapHeight = map->height;
        mapWidth = map->width;
        this->setSceneRect(0, 0, SCENEWIDTH, SCENEHEIGHT);
        tiles = new QGraphicsItem**[mapHeight];
        int x = 0; int y = 0; int tileSize = this->width()/mapWidth;
        qDebug() << this->width() << " " << mapWidth << " " << mapHeight << " " << tileSize;

        for(int i = 0; i < mapHeight; i++){
            tiles[i] = new QGraphicsItem*[mapWidth];
            for(int j = 0; j < mapWidth; j++){
                CellStatus status = gameController->whatInCell(j, i);
//                qDebug() << status;
                tiles[i][j] = defineEntities(status);
                tiles[i][j]->setPos(x, y);
                this->addItem(tiles[i][j]);
    //            qDebug() << "x: " << x << ", y:" << y << " tiles: " << tiles[i][j].x() << " " <<  tiles[i][j].y() << " " << tileSize;
                x += tileSize;
            }
            x = 0;
            y += tileSize;
        }
}

MapView::~MapView()
{
    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapWidth; j++){
            this->removeItem(tiles[i][j]);
        }
    }

    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapWidth; j++){
            delete tiles[i][j];
        }
        delete [] tiles[i];
    }
    delete [] tiles;
}

QGraphicsItem * MapView::defineEntities(CellStatus status)
{
    switch(status){
        case PLAYER:
            return new PlayerGraphicsItem();
            break;
        case EMPTY:
            return  new EmptyGraphicsItem();
            break;
        case COIN:
            return  new CoinGraphicsItem();
            break;
        case BOMB:
            return new BombGraphicsItem();
            break;
        case HITPOINT:
            return new HitpointGraphicsItem();
        case WALL:
            return new WallGraphicsItem();
      default:
           return  new EmptyGraphicsItem();
    }

}

void MapView::drawMap()
{
//    qDebug() << gameController->getPlayer()->dead();
  static int c = 0;
    int x = 0; int y = 0; int tileSize = this->width()/mapWidth;
    for(int i = 0; i < mapHeight; i++){
        for(int j = 0; j < mapWidth; j++){
              if(gameController->cellChanged(j, i)){
//                  qDebug() << "redraw: " << j << " " << i << (++c);
                  CellStatus status = gameController->whatInCell(j, i);
                  this->removeItem(tiles[i][j]);
                  delete tiles[i][j];
                  tiles[i][j] = defineEntities(status);
                  tiles[i][j]->setPos(x, y);
                  this->addItem(tiles[i][j]);
              }
            x += tileSize;
        }
        x = 0;
        y += tileSize;
    }
}









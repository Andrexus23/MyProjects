#ifndef MAPVIEW_H
#define MAPVIEW_H
#include <QGraphicsRectItem>
#include "QPainter"
#include "QGraphicsView"
#include "QVector"
#include "squareview.h"

class MapView: public QGraphicsRectItem
{
public:
    MapView(QGraphicsView * view, int logicSize, int guiSize);
    ~MapView();
    void drawSquare(int x, int y, int size);
private:
    QGraphicsView * view;
    QGraphicsScene * scene;
    QVector <SquareView * > squares;
    int coef;

};

#endif // MAPVIEW_H

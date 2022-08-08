#include "../inc/mapview.h"
#include "QDebug"
#include <cmath>
MapView::MapView(QGraphicsView * view, int logicSize, int guiSize): view(view){
    scene = view->scene();
    float choose = (float)((float)guiSize / (float)logicSize);
    float diff = fabs((float)choose - (int)(choose));
    coef = (diff >= 0.5) ? (int)choose + 1 : (int)choose;
//    qDebug() << guiSize << " " << logicSize <<  " " << diff << " "  << coef;
}

MapView::~MapView()
{
    for(auto & i : squares)
        delete i;
}

void MapView::drawSquare(int x, int y, int size)
{
    SquareView * square = new SquareView(x, y, size, coef, scene);
    squares.push_back(square);
}

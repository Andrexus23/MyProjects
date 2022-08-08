#ifndef SQUAREVIEW_H
#define SQUAREVIEW_H
#include "QGraphicsRectItem"
#include "QGraphicsTextItem"
#include <QGraphicsScene>
class SquareView
{
public:
    SquareView(int x, int y, int size, int coef, QGraphicsScene * scene);
    ~SquareView();
private:
    int x;
    int y;
    int size;
    QGraphicsRectItem * square;
    QGraphicsTextItem * text;
    QGraphicsScene * scene;
};

#endif // SQUAREVIEW_H

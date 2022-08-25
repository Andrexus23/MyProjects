#include "../../inc/objectsView/PlayerGraphicsItem.h"


PlayerGraphicsItem::PlayerGraphicsItem(QObject *parent):QObject(parent), QGraphicsItem(){
}

PlayerGraphicsItem::~PlayerGraphicsItem()
{

}


QRectF PlayerGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, CELLSIZE, CELLSIZE);
}

void PlayerGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::lightGray);
    painter->setPen(Qt::lightGray);
    painter->drawRect(0, 0, CELLSIZE, CELLSIZE);
    painter->setBrush(Qt::black);
    painter->setPen(Qt::black);
    painter->drawRect(0 + CELLSIZE/3  , (CELLSIZE/2), (CELLSIZE/4), (CELLSIZE/2));
    painter->drawEllipse(CELLSIZE/2.9, CELLSIZE/4, CELLSIZE/4, CELLSIZE/4);
    painter->drawRect(CELLSIZE/3 + (CELLSIZE/4) + 2, (CELLSIZE/2) + CELLSIZE/6, 7, 2);
    painter->drawRect(CELLSIZE/3 + (CELLSIZE/4) + 2, (CELLSIZE/2) + CELLSIZE/6, 2, 5);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

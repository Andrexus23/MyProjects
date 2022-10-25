#include "../../inc/objectsView/BombGraphicsItem.h"
#include "QFont"

BombGraphicsItem::BombGraphicsItem(QObject *parent)
{

}

BombGraphicsItem::~BombGraphicsItem()
{

}

QRectF BombGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, CELLSIZE, CELLSIZE);
}

void BombGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::lightGray);
    painter->setPen(Qt::lightGray);
    painter->drawRect(0, 0, CELLSIZE, CELLSIZE);
    painter->setBrush(Qt::red);
    painter->setPen(Qt::black);
    painter->drawEllipse(QPointF(CELLSIZE/2, CELLSIZE/2), (CELLSIZE/3)*1.3, (CELLSIZE/3)*1.3);
    painter->setFont(QFont("Arial", 7));
    painter->drawText(QPointF(CELLSIZE/3.8, CELLSIZE/1.7), "bomb");
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

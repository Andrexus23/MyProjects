#include "../../inc/objectsView/CoinGraphicsItem.h"

CoinGraphicsItem::CoinGraphicsItem(QObject *parent)
{
}



CoinGraphicsItem::~CoinGraphicsItem()
{

}

QRectF CoinGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, CELLSIZE, CELLSIZE);
}

void CoinGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::lightGray);
    painter->setPen(Qt::lightGray);
    painter->drawRect(0, 0, CELLSIZE, CELLSIZE);
    painter->setBrush(Qt::yellow);
    painter->setPen(Qt::black);
    painter->drawEllipse(QPoint(CELLSIZE/2, CELLSIZE/2), (CELLSIZE/3), (CELLSIZE/3));
    painter->drawEllipse(QPoint(CELLSIZE/2, CELLSIZE/2), (CELLSIZE/3.5), (CELLSIZE/3.5));
    painter->drawText(QPointF(CELLSIZE/2.2, CELLSIZE/1.7), "$");
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

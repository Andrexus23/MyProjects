#include "../../inc/objectsView/WallGraphicsItem.h"

WallGraphicsItem::WallGraphicsItem(QObject *parent)
{

}

WallGraphicsItem::~WallGraphicsItem()
{

}

QRectF WallGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, CELLSIZE, CELLSIZE);
}

void WallGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->setPen(Qt::lightGray);
    painter->drawRect(0, 0, CELLSIZE, CELLSIZE);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}


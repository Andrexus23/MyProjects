#include "../../inc/objectsView/EmptyGraphicsItem.h"


EmptyGraphicsItem::EmptyGraphicsItem(QObject *parent)
{
}



EmptyGraphicsItem::~EmptyGraphicsItem()
{

}

QRectF EmptyGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, CELLSIZE, CELLSIZE);
}

void EmptyGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::lightGray);
    painter->setPen(Qt::lightGray);
    painter->drawRect(0, 0, CELLSIZE, CELLSIZE);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

#include "../../inc/objectsView/HitpointGraphicsItem.h"


HitpointGraphicsItem::HitpointGraphicsItem(QObject *parent)
{

}

HitpointGraphicsItem::~HitpointGraphicsItem()
{

}

QRectF HitpointGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, CELLSIZE, CELLSIZE);
}

void HitpointGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::lightGray);
    painter->setPen(Qt::lightGray);
    painter->drawRect(0, 0, CELLSIZE, CELLSIZE);

    painter->setBrush(Qt::red);
    painter->setPen(Qt::red);
    painter->drawEllipse(QPoint( CELLSIZE/3, CELLSIZE/3), CELLSIZE/4.2, CELLSIZE/4.2);
    painter->drawEllipse(QPoint( 2*CELLSIZE/3, CELLSIZE/3), CELLSIZE/4.2, CELLSIZE/4.2);

    QPainterPath path;
    QPolygon poly;
    poly << QPoint(CELLSIZE/12 + 1, CELLSIZE/3 + 3) << QPoint(CELLSIZE/2, CELLSIZE-1)
         << QPoint(CELLSIZE*11/12 - 1, CELLSIZE/3 + 3) << QPoint(CELLSIZE/12 + 1, CELLSIZE/3 + 3);
    path.addPolygon(poly);
    painter->drawPolygon(poly);
    painter->fillPath(path, Qt::red);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

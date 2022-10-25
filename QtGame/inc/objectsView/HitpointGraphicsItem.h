#ifndef HITPOINTGRAPHICSITEM_H
#define HITPOINTGRAPHICSITEM_H
#include "QGraphicsItem"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "../cell.h"

class HitpointGraphicsItem : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    explicit HitpointGraphicsItem(QObject * parent=0);
    ~HitpointGraphicsItem();
private:
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // HITPOINTGRAPHICSITEM_H

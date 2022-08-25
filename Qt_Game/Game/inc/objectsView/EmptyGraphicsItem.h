#ifndef EMPTYGRAPHICSITEM_H
#define EMPTYGRAPHICSITEM_H

#include "QGraphicsItem"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "../cell.h"

class EmptyGraphicsItem : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    explicit EmptyGraphicsItem(QObject * parent=0);
    ~EmptyGraphicsItem();
private:
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // EMPTYGRAPHICSITEM_H

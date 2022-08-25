#ifndef WALLGRAPHICSITEM_H
#define WALLGRAPHICSITEM_H

#include "QGraphicsItem"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "../cell.h"

class WallGraphicsItem : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    explicit WallGraphicsItem(QObject * parent=0);
    ~WallGraphicsItem();
private:
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // WALLGRAPHICSITEM_H

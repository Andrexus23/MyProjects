#ifndef BOMBGRAPHICSITEM_H
#define BOMBGRAPHICSITEM_H
#include "QGraphicsItem"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "../cell.h"

class BombGraphicsItem : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    explicit BombGraphicsItem(QObject * parent=0);
    ~BombGraphicsItem();
private:
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BOMBGRAPHICSITEM_H

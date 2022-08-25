#ifndef COINGRAPHICSITEM_H
#define COINGRAPHICSITEM_H

#include "QGraphicsItem"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "../cell.h"

class CoinGraphicsItem : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    explicit CoinGraphicsItem(QObject * parent=0);
    ~CoinGraphicsItem();
private:
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};


#endif // COINGRAPHICSITEM_H

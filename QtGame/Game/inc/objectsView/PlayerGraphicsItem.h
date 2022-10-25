#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include "QGraphicsItem"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "../cell.h"


class PlayerGraphicsItem : public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    explicit PlayerGraphicsItem(QObject * parent=0);
    ~PlayerGraphicsItem();
private:
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // PLAYERVIEW_H

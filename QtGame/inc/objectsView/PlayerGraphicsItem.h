#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H
#include "QGraphicsItem"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "../entities/player.h"
#include "../cell.h"


class PlayerGraphicsItem : public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    explicit PlayerGraphicsItem(QObject * parent=0, Player * player=nullptr);
    ~PlayerGraphicsItem();
private:
     Player* player;
     QRectF boundingRect() const;
     void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};
#endif // PLAYERVIEW_H

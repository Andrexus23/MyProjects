#ifndef CUSTOMGRAPHICSITEM_H
#define CUSTOMGRAPHICSITEM_H
#include "QGraphicsItem"
#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include "../cell.h"

class CustomGraphicsItem : public QObject, public QGraphicsItem{
    Q_OBJECT
public:
    explicit CustomGraphicsItem(QObject * parent=0);
    virtual ~CustomGraphicsItem(){};
    virtual CellStatus & getStatus() = 0;
private:
    QRectF boundingRect() const {return QRectF();};
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){};
     CellStatus status;
};
#endif // CUSTOMGRAPHICSITEM_H

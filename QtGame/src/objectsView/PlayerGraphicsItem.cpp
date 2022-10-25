#include "../../inc/objectsView/PlayerGraphicsItem.h"
#include "QDebug"

PlayerGraphicsItem::PlayerGraphicsItem(QObject *parent, Player* player):QObject(parent), QGraphicsItem(){
        this->player = player;
}

PlayerGraphicsItem::~PlayerGraphicsItem()
{

}


QRectF PlayerGraphicsItem::boundingRect() const
{
    return QRectF(0, 0, CELLSIZE, CELLSIZE);
}

void PlayerGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(player != nullptr){
        painter->setBrush(Qt::lightGray);
        painter->setPen(Qt::lightGray);
        painter->drawRect(0, 0, CELLSIZE, CELLSIZE);
        painter->setBrush(Qt::black);
        painter->setPen(Qt::black);

        painter->drawEllipse(CELLSIZE/2.9, CELLSIZE/4, CELLSIZE/4, CELLSIZE/4);

        switch(player->getDirection()){
        case RIGHT:
            painter->drawRect(CELLSIZE/3 + (CELLSIZE/4) + 2, (CELLSIZE/2) + CELLSIZE/6, 7, 2);
            painter->drawRect(CELLSIZE/3 + (CELLSIZE/4) + 2, (CELLSIZE/2) + CELLSIZE/6, 2, 5);
            painter->drawRect(0 + CELLSIZE/3  , (CELLSIZE/2), (CELLSIZE/4), (CELLSIZE/2));
            break;
        case LEFT:
            painter->drawRect(CELLSIZE/3 - (CELLSIZE/4) + 1, (CELLSIZE/2) + CELLSIZE/6, 7, 2);
            painter->drawRect(CELLSIZE/3 - (CELLSIZE/6) + 2, (CELLSIZE/2) + CELLSIZE/6, 2, 5);
            painter->drawRect(0 + CELLSIZE/3  , (CELLSIZE/2), (CELLSIZE/4), (CELLSIZE/2));
            break;
        case UP:
            painter->drawRect(CELLSIZE/3 + 4 , CELLSIZE/9, 2, 4);
            painter->drawRect(0 + CELLSIZE/3  , (CELLSIZE/2), (CELLSIZE/4), (CELLSIZE/4));
            break;
        case DOWN:
            painter->drawRect(CELLSIZE/3 + 4, (CELLSIZE/2) + (CELLSIZE/4),  2, 4);
            painter->drawRect(0 + CELLSIZE/3  , (CELLSIZE/2), (CELLSIZE/4), (CELLSIZE/4));
            break;
         default:
            break;
        }
   }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

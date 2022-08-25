#ifndef DRAWER_H
#define DRAWER_H
#include "../inc/MapView.h"
#include "QPainter"

class Drawer:public QWidget{
public:
    Drawer();
    void drawPlayer(QGraphicsRectItem * item);
    ~Drawer();
private:
    QPainter * painter;
};

#endif // DRAWER_H

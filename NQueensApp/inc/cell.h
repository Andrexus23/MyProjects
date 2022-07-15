#ifndef CELL_H
#define CELL_H

#include <QGraphicsRectItem>
#include <QBrush>


class Cell : public QGraphicsRectItem{
public:
    Cell(int coef, QGraphicsItem * parent=0);
    ~Cell();
    void setQueen();
    int xCoord;
    int yCoord;
private:
    QBrush brush;
    QColor originalColor;
    QString queenColor;
    bool hasQueen = false;

};

#endif // CELL_H

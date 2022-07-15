#ifndef BOARD_H
#define BOARD_H
#include <QGraphicsRectItem>
#include <cell.h>

class Board{
public:
    Board(int bSize, int bSide) : boardSize(bSize), boardSide(bSide) {};
    void drawCells(int xFrom = 0, int yFrom = 0);
private:
    QList <Cell *> queensList;
    int boardSize; // размер стороны в количестве ячеек
    int boardSide; // Размер одной ячейки в пикселях
    Cell ** board;
};


#endif // BOARD_H

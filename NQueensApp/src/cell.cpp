#include "cell.h"

Cell::Cell(int side, QGraphicsItem *parent)
{
    setRect(0,0,side,side);
}

Cell::~Cell()
{

}

void Cell::setQueen()
{
    hasQueen = true;
}

#include "../inc/cell.h"


Cell::Cell(CellStatus argStatus):status(argStatus), prevStatus(argStatus)
{

}

CellStatus & Cell::getStatus()
{
    return status;
}

CellStatus &Cell::getPrevStatus()
{
    return prevStatus;
}

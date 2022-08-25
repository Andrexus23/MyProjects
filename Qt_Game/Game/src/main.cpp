#include <QApplication>
#include "../inc/map.h"
#include "../inc/GameWindow.h"
#include "QDebug"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w; w.show();
    return a.exec();
}

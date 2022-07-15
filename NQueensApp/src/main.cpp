#include <QtWidgets>
#include <QApplication>
#include "gui.h"
#include<QDesktopWidget>
#include "board.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Gui g;
    g.show();
    QMessageBox::information(&g, "Добро пожаловать", "Приложение визуализирует задачу расстановки N ферзей на доске размера N таким"
                                                       " образом, чтобы никакие 2 ферзя не били друг друга. N >=4.");
    return app.exec();
}

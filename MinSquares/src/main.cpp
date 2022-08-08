#include <QApplication>
#include "../inc/appview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AppView  app;
    app.show();
    return a.exec();
}

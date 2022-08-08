#ifndef APPVIEW_H
#define APPVIEW_H
#include <QGraphicsView>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include "mapview.h"
#include "logic.h"
#include <QLabel>
#include <QDateTime>

class AppView :public QWidget
{
    Q_OBJECT
public:
    AppView();
    ~AppView();
    QGraphicsScene *scene;
private slots:
    void runButtonClicked();
private:
    QGraphicsView * view;
    QPushButton * runButton;
    QLineEdit * enterSizeLineEdit;
    MapView * mapView;
    QHBoxLayout * inputLayout;
    QGridLayout * mainLayout;
    QLabel * timeLabel;
    Logic * logic;
    int difference;
    int width = 800;
    int height = 600;
    int viewSize = 400;
    int guiSize;
    int logicSize;

};

#endif // APPVIEW_H

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsView>
#include "QGridLayout"
#include "QPushButton"
#include "GameController.h"
#include "../inc/MapView.h"
#include "QWidget"

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow();
    ~GameWindow();
     void keyPressEvent(QKeyEvent *event) override;
private slots:
     void update();
private:
    QGraphicsView * view;
    MapView * mapView;
    Map & map = Map::instance();
    QGridLayout * layout;
    QPushButton * newGameButton;
    GameController * gameController;
    QTimer *timer;
};
#endif

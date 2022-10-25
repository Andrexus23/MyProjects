#include "../inc/GameWindow.h"
#include "QTimer"
#include "QScrollBar"

GameWindow::GameWindow()
{
    layout = new QGridLayout;
    setLayout(layout);

    gameController = new GameController();

    view = new QGraphicsView;
    mapView = new MapView(&map, gameController);
    view->setScene(mapView);
    view->setFixedSize(VIEWWIDTH, 600);
    this->setFixedSize(900, 620);
    view->horizontalScrollBar()->setValue(Qt::ScrollBegin);
    view->verticalScrollBar()->setValue(Qt::ScrollBegin);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    newGameButton = new QPushButton("New game");
    layout->addWidget(view, 0, 0, 10, 10);
    layout->addWidget(newGameButton, 0, 100, 1, 2);
    timer = new QTimer(this);
    timer->start(50);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}


GameWindow::~GameWindow()
{
    delete mapView;
    delete view;
    delete layout;
    delete newGameButton;
    delete gameController;
    delete timer;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_W:
            gameController->moveUp();
            break;
         case Qt::Key_S:
            gameController->moveDown();
            break;
         case Qt::Key_A:
            gameController->moveLeft();
            break;
         case Qt::Key_D:
            gameController->moveRight();
            break;
         default:
            break;
    }
}

void GameWindow::update()
{
    static int c = 0;
    static int windowWidth = VIEWWIDTH;
    static int ticks = 0;
    gameController->update();
    if(gameController->gameOver){
        qDebug() << "Player's dead";
    }
    if(gameController->someThingChanged()){
        mapView->drawMap();
    }

    if(((gameController->getPlayer()->getX()*CELLSIZE) >= windowWidth - 200) && (gameController->getPlayer()->getDirection() == RIGHT)){
//        qDebug() << windowWidth << " " << windowWidth;
        c += 200;
        windowWidth += 200;
        view->horizontalScrollBar()->setSliderPosition(c);
    }else if(((gameController->getPlayer()->getX()*CELLSIZE) <= windowWidth - 600) &&  (gameController->getPlayer()->getDirection() == LEFT)){
//        qDebug() << windowWidth << " " << windowWidth;
        c -= 200;
        windowWidth -= 200;
        view->horizontalScrollBar()->setSliderPosition(c);
    }


    if(gameController->gameOver) {
        timer->stop();
    }
    ticks++;
//    qDebug() << "Timer's working: " << ticks;
}

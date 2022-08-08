#include "../inc/appview.h"
#include <QDebug>
#include <QRegExpValidator>
#include <QMessageBox>
#include <cmath>

AppView::AppView()
{
    setFixedSize(width, height);
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);
    enterSizeLineEdit = new QLineEdit();
    runButton = new QPushButton("Run");
    guiSize = 550;
    mainLayout = new QGridLayout;
    setLayout(mainLayout); // устанавливаем слой
    scene->setSceneRect(QRect(0, 0, guiSize, guiSize-2));
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setFixedSize(guiSize, guiSize);
     // Устанавливаем область графической сцены
    mainLayout->addWidget(view, 0, 0, 10, 10, Qt::AlignTop);
    inputLayout = new QHBoxLayout;
    mainLayout->addLayout(inputLayout, 0, 10, 1, 4);
    enterSizeLineEdit->setFixedSize(50, 30);
    runButton->setFixedHeight(30);
    inputLayout->addWidget(enterSizeLineEdit);
    inputLayout->addWidget(runButton);

    connect(runButton, SIGNAL(clicked()), this, SLOT(runButtonClicked()));
    enterSizeLineEdit->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]*"), enterSizeLineEdit));

    timeLabel = new QLabel();
    mainLayout->addWidget(timeLabel, 10, 0, 1, 4);

    logic = nullptr;
    mapView = nullptr;
}

AppView::~AppView()
{
    delete logic;
    delete mapView;
    delete view;
    delete scene;
    delete mainLayout;
    delete inputLayout;
    delete timeLabel;
}

void AppView::runButtonClicked()
{
    QString text = enterSizeLineEdit->text();
    if(!text.isEmpty()){
        logicSize = text.toInt();
        if(logicSize > 50)
              QMessageBox::warning(this, "Ошибка", "Слишком большая сторона доски");
            if(logicSize < 2)
              QMessageBox::warning(this, "Ошибка", "Слишком маленькая сторона доски");
            else{
                delete mapView; mapView = nullptr;
                delete logic; logic = nullptr;
                QDateTime start = QDateTime::currentDateTime();
                logic = new Logic(logicSize);
                QDateTime stop = QDateTime::currentDateTime();

                difference = (start.msecsTo(stop));

                mapView = new MapView(view, logicSize, guiSize);
                auto & squares = logic->savedSquares;
                for(auto & square: squares){
//                    qDebug() << square.x << " " << square.y << " " << square.size;
                    mapView->drawSquare(square.x, square.y, square.size);
                }

                string tmlbl = "Algorithm running time: " + std::to_string(difference) + " msec";
                timeLabel->setText(QString(tmlbl.c_str()));
            }

       }
}

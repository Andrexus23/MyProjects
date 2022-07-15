#include "gui.h"
#include <QDesktopWidget>
#include <QMessageBox>

Gui::Gui()
{
    setWindowTitle("NQueens");
    enterNLineEdit = new QLineEdit();
    runButton = new QPushButton("Run");
    prevVarButton = new QPushButton("Previous");
    nextVarButton = new QPushButton("Next");
    varLabel = new QLabel();
    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    QGridLayout * mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout); // устанавливаем слой

    mainLayout->addWidget(enterNLineEdit, 0, 30, 1, 2);
    mainLayout->addWidget(runButton, 1, 30, 1, 2);
    mainLayout->addWidget(varLabel, 2, 30, 1, 2);
    mainLayout->addWidget(prevVarButton, 3, 30, 1, 1);
    mainLayout->addWidget(nextVarButton, 3, 31, 1, 1);

    boardSide = 400;

    view->resize(boardSide, boardSide);
    scene->setSceneRect(0, 0, view->width(), view->height());
    prevVarButton->setEnabled(false);
    nextVarButton->setEnabled(false);

    mainLayout->addWidget(view, 0, 0, 29, 29);
    connect(runButton, SIGNAL(clicked()), this, SLOT(runButtonClicked()));
    connect(prevVarButton, SIGNAL(clicked()), this, SLOT(prevVarButtonClicked()));
    connect(nextVarButton, SIGNAL(clicked()), this, SLOT(nextVarButtonClicked()));

    enterNLineEdit->setValidator(new QRegExpValidator(QRegExp("[1-9][0-9]*"), enterNLineEdit));

}

Gui::~Gui()
{

}

void Gui::drawBoard(int xFrom, int yFrom, QVector<int> & solution)
{
    for(auto i : cellsArray){
        scene->removeItem(i); // удаление ячейки со сцены не освобождает выделенную под неё память
        delete i;
    }
    cellsArray.clear();

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    scene->setBackgroundBrush(brush);

    int cellSide = boardSide / boardSize;
    for(int i = 0; i < boardSize; i++){
        for(int j = 0; j < boardSize; j++){
              Cell * cell = new Cell(cellSide);
              cell->xCoord = j;
              cell->yCoord = i;
              if(solution[i] == j){
                  cell->setBrush(Qt::red);
              }
              cell->setPos(xFrom + cellSide*j, yFrom + cellSide*i);
              scene->addItem(cell);
              cellsArray.push_back(cell);
        }
    }
}



void Gui::runButtonClicked()
{
    delete logic;
    QString text = enterNLineEdit->text();

    if(!(prevVarButton->isEnabled())){
        prevVarButton->setEnabled(true);
        nextVarButton->setEnabled(true);
    }

    if(!text.isEmpty()){
        boardSize = text.toInt();
        if(boardSize > 100)
          QMessageBox::warning(this, "Ошибка", "Слишком большая сторона доски");
        if(boardSize < 4)
          QMessageBox::warning(this, "Ошибка", "Слишком маленькая сторона доски");
        else{
            logic = new Logic(boardSize);
            QString str =  QString::number(1) + " of " + QString::number(logic->getSolutionsCount());
            varLabel->setText(str);
            drawBoard(0, 0, logic->getSolution(0));
        }
        qDebug() << boardSize;
    }
}

void Gui::prevVarButtonClicked()
{
    int curSol = logic->getCurrentSolution();
    if(curSol == 0)
        return;
    else{
        curSol--;
        logic->setCurrentSolution(curSol);
        varLabel->setText(QString::number(curSol+1) + " of " + QString::number(logic->getSolutionsCount()));
        drawBoard(0, 0, logic->getSolution(curSol));
    }
}

void Gui::nextVarButtonClicked()
{
    int curSol = logic->getCurrentSolution();
    if(curSol == logic->getSolutionsCount() - 1)
        return;
    else{
        curSol++;
        logic->setCurrentSolution(curSol);
        varLabel->setText(QString::number(curSol+1) + " of " + QString::number(logic->getSolutionsCount()));
        drawBoard(0, 0, logic->getSolution(curSol));
    }
}





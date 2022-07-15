#ifndef GUI_H
#define GUI_H
#include "QWidget"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QString>
#include <QDebug>
#include <QRegExpValidator>
#include <QGraphicsRectItem>
#include <cell.h>
#include <logic.h>

class Gui: public QWidget
{
    Q_OBJECT // для работы механизма сигналов и слотов
public:
    Gui();
    ~Gui();
    void drawBoard(int xFrom, int yFrom, QVector<int> & solution);
private:
    QPushButton * runButton;
    QPushButton * prevVarButton;
    QPushButton * nextVarButton;
    QLabel * varLabel;
    QLineEdit * enterNLineEdit;
    QGraphicsScene * scene;
    QGraphicsView * view;
    QVector<Cell*> cellsArray;
    Logic * logic = nullptr;
    int boardSide;
    int boardSize;
private slots:
    void runButtonClicked();
    void prevVarButtonClicked();
    void nextVarButtonClicked();
};

#endif // GUI_H

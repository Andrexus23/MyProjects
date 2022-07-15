#ifndef LOGIC_H
#define LOGIC_H
#include "algorithm"
#include "QVector"
#include <QDebug>
#define MAXSOLCOUNT 3
class Logic
{
    int attempts = 0;
    int solutionsCount = 0;
    int currentSolution = 0;
    QVector<QVector<int>> * solutions = nullptr;
public:
    Logic(int n);
    void algorithm(QVector<int>&v, int leftToPlace, int totalToPlace);
    bool isLegal(QVector<int>&v);
    void addToSolutions(QVector<int>&v);
    void printSolutions();
    int getSolutionsCount();
    int getCurrentSolution();
    void setCurrentSolution(int number);
    QVector<int> & getSolution(int number=0);
    ~Logic();
};

#endif // LOGIC_H

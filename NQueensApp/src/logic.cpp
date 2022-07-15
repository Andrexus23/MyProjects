#include "logic.h"
#include <iostream>
#include <QtMsgHandler>


Logic::Logic(int n)
{
    solutions = new QVector<QVector<int>>();
    QVector<int> v;
    v.reserve(n);
    algorithm(v, n, n);
}

void Logic::algorithm(QVector<int> &v, int leftToPlace, int totalToPlace)
{
    if(solutionsCount >= MAXSOLCOUNT) return; // если количество уже найденных решений уже 3, то больше не ищем
    if(leftToPlace == 0){
        ++solutionsCount;
        addToSolutions(v);
        return;
    }
    v.push_back(0);
    for(int i =0; i < totalToPlace; ++i){
        v.back() = i;
        if(isLegal(v)){
            algorithm(v, leftToPlace - 1, totalToPlace);
        }
    }
    v.pop_back();
}

bool Logic::isLegal(QVector<int> &v)
{
    attempts++;
    int value = v.back();
    // тест по горизонтали
    for(int i = 0; i < v.size()-1; ++i){
        if(v[i] == value){
            return false;
        }
    }
    // тест по диагонали
    int offset = 1;
    for(int i = v.size()-2; i>=0;--i){
        if(value == v[i] + offset){ // вверх
            return false;
        }
        if(value == v[i] - offset){ // вниз
            return false;
        }
        ++offset;
    }
    return true;
}

void Logic::addToSolutions(QVector<int> & v)
{
    QVector<int> sol;
    sol.append(v);
    solutions->push_back(sol);
}

void Logic::printSolutions()
{
    for(auto & it: *solutions){
        for(auto & sol : it){
            qDebug() << sol;
        }
        qDebug() << endl;
    }
}

int Logic::getSolutionsCount()
{
    return solutionsCount;
}

int Logic::getCurrentSolution()
{
    return currentSolution;
}

void Logic::setCurrentSolution(int number)
{
    if(number >= solutionsCount)
        qDebug() << "setCurrentSolution: Incorrect number";
    else
        currentSolution = number;
}

QVector<int> &Logic::getSolution(int number)
{
    if(number >= solutionsCount)
        return (*solutions)[0];

    return (*solutions)[number];
}



Logic::~Logic()
{
    delete solutions;
}

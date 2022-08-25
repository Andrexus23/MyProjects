#ifndef ITERATOR_H
#define ITERATOR_H
#include "iostream"
#include "cell.h"
class Iterator{
public:
    Iterator(Cell ** map, int width, int height);
    void next();
    void first();
    bool isDone() const;
    bool rowEnd() const;
    Cell & current();

private:
    Cell ** map{};
    int width{};
    int height{};
    int iterRowCounter = 0;
    int iterColCounter = 0;
    bool containerOver = false;
};
#endif // ITERATOR_H

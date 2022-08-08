#ifndef LOGIC_H
#define LOGIC_H

#include "iostream"
#include "vector"
#include "algorithm"
#include "stack"
using namespace std;

struct Square{
    int x;
    int y;
    int size;
};

class Logic {
public:
    explicit Logic(int N);
    ~Logic();
    void preprocess();
    void saveSolution();
    void setSquare(Square & info);
    void deleteSquare(Square & info);
    void fillArea(int depth);
    bool isFreeArea(int x, int y, int range);
    Square findOpportunity(int xFrom, int yFrom, int maxLen);
    Square getSquare(int x, int y, int currentSize);
    vector<Square> savedSquares;
private:
    int calledTimes = 0;
    int size;
    int fixedSize;
    int gcd = 1;
    int alreadySetCount = 0;
    int minCount = INT32_MAX;
    vector<vector<int>> * map;
    vector<vector<int>> savedMap;
    vector<Square> squares;
};

#endif // LOGIC_H

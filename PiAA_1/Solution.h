#ifndef PIAA_1_PERFECT_SOLUTION_H
#define PIAA_1_PERFECT_SOLUTION_H
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

class Solution {
public:
    explicit Solution(int N);
    ~Solution();
    void printMap(int n);
    void preprocess();
    void printSolution(vector<Square> & obj) const;
    void saveSolution();
    void setSquare(Square & info);
    void deleteSquare(Square & info);
    void fillArea(int depth);
    void fillAreaIter(int x, int y);
    bool isFreeArea(int x, int y, int range);
    Square findOpportunity(int xFrom, int yFrom, int maxLen);
    Square getSquare(int x, int y, int currentSize);
    static void printIndent(int n);
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
    vector<Square> savedSquares;
};


#endif //PIAA_1_PERFECT_SOLUTION_H

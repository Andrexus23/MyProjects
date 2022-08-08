#include "../inc/logic.h"
#include "QDebug"

Logic::Logic(int N) :size(N){
    int c = 2;
    if (size % 2 == 0) {
        gcd = 1;
        fixedSize = size;
    } else {
        while (c < size) {
            if (size % c == 0) {
                gcd = c;
            }
            c++;
        }
        fixedSize = (int) (size / gcd);
    }
    map = new vector<vector<int>>(fixedSize);
    for(auto & i: *map){
        i.resize(fixedSize);
    }
    preprocess();
}

Logic::~Logic() {
    delete  map;
}



void Logic::preprocess() {
    calledTimes = 0;
    if(size % 2 == 0){
        squares.resize(4);
        squares[0] = {0, 0, fixedSize/ 2};
        squares[1] = {squares[0].x, squares[0].y+fixedSize/2, fixedSize/2};
        squares[2] = {squares[0].x+fixedSize/2, squares[0].y, fixedSize/2};
        squares[3] = {squares[0].x+fixedSize/2, squares[0].y+fixedSize/2, fixedSize/2};
        for(auto & i: squares) setSquare(i);
        saveSolution();
        minCount = 4;
    } else{
        squares.push_back({0, 0, fixedSize - (fixedSize / 2 + 1)});
        squares.push_back({fixedSize / 2, 0, fixedSize - (fixedSize / 2)});
        squares.push_back({(fixedSize / 2) + 1, (fixedSize / 2) + 1 ,fixedSize - (fixedSize / 2 + 1) });
        alreadySetCount = (int)squares.size(); // уже поставлено
        for(auto & i: squares) setSquare(i);
        fillArea(alreadySetCount);
    }


}


void Logic::saveSolution() {
    savedSquares.clear();
    for(auto & i: squares){
        savedSquares.push_back({i.x*gcd, i.y*gcd, i.size*gcd});
    }
}

void Logic::setSquare(Square &info) {
    for(int i = 0; i != info.size; i++){
        for(int j = 0; j != info.size; j++)
            (*map)[info.y + i][info.x + j] = info.size;
    }
}

void Logic::deleteSquare(Square &info) {
    for(int i = 0; i != info.size; i++){
        for(int j = 0; j != info.size; j++)
            (*map)[info.y + i][info.x + j] = 0;
    }
}

void Logic::fillArea(int depth) {
    if(depth + 1 >= minCount){
        return;
    }
    Square opportunity{};
    calledTimes++;
    opportunity = findOpportunity(0, fixedSize / 2, fixedSize / 2);


    for(int i = opportunity.size; i > 0; i--) {
        opportunity.size = i;
        setSquare(opportunity);
        squares.push_back(opportunity);

        if(isFreeArea(0, fixedSize / 2, fixedSize)) {
            fillArea(depth + 1);
        }
        else{
            if(depth + 1 < minCount){
                minCount = depth + 1;
                saveSolution();

            }
            deleteSquare(opportunity);
            squares.pop_back();
            return;
        }

        deleteSquare(opportunity);
        squares.pop_back();
    }
}

bool Logic::isFreeArea(int x, int y, int range) {
    for(int i = y; i < range; i++){
        for(int j = x; j < range; j++){
            if((*map)[i][j] == 0) {
                return true;
            }
        }
    }
    return false;
}

Square Logic::findOpportunity(int xFrom, int yFrom, int maxLen) {
    auto & refMap = (*map);
    for(int i = yFrom; i <= yFrom + maxLen; i++){
        for(int j = xFrom; j <= xFrom + maxLen; j++){
            if(refMap[i][j] == 0){
                int curSize = maxLen;
                while(curSize > 0){
                    Square s = getSquare(j, i, curSize);
                    if(s.size != 0) return s;
                    curSize--;
                }
                return {-1, -1, 0};
            }
        }
    }
    return {-1, -1, 0};
}

Square Logic::getSquare(int x, int y, int currentSize) {
    auto & refMap = (*map);
    int futSize =  currentSize;
    if(x + futSize > fixedSize) return {-1, -1, 0};
    if(y + futSize > fixedSize) return {-1, -1, 0};

    for (int i = y; i < y + futSize; i++) {
        for (int j = x; j < x +  futSize; j++) {
            if (refMap[i][j] != 0){
                return {-1, -1, 0};
            }
        }
    }

    return {x, y, futSize};
}


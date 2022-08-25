#include "Solution.h"


Solution::Solution(int N) :size(N){
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

Solution::~Solution() {
    delete  map;
}

void Solution::printMap(int n) {
    for(auto & i: *map){
        printIndent(n);
        for(auto & j : i){
            cout << j << " ";
        }
        cout << "\n";
    }
}

void Solution::preprocess() {
    calledTimes = 0;
    if(size % 2 == 0){
        squares.resize(4);
        squares[0] = {0, 0, fixedSize/ 2};
        squares[1] = {squares[0].x, squares[0].y+fixedSize/2, fixedSize/2};
        squares[2] = {squares[0].x+fixedSize/2, squares[0].y, fixedSize/2};
        squares[3] = {squares[0].x+fixedSize/2, squares[0].y+fixedSize/2, fixedSize/2};
        for(auto & i: squares) setSquare(i);
        minCount = 4;
        saveSolution();
    } else{
//        squares.push_back({fixedSize / 2 + 1, 0, fixedSize - (fixedSize / 2 + 1)});
//        squares.push_back({0, fixedSize / 2 + 1, fixedSize - (fixedSize / 2 + 1)});
//        squares.push_back({fixedSize / 2, fixedSize / 2, fixedSize - (fixedSize / 2)});
        squares.push_back({0, 0, fixedSize - (fixedSize / 2 + 1)});
        squares.push_back({fixedSize / 2, 0, fixedSize - (fixedSize / 2)});
        squares.push_back({(fixedSize / 2) + 1, (fixedSize / 2) + 1 ,fixedSize - (fixedSize / 2 + 1) });
        alreadySetCount = (int)squares.size(); // уже поставлено
        for(auto & i: squares) setSquare(i);
//        printMap(0);
//        fillArea(alreadySetCount);
//        fillAreaIter(0, fixedSize / 2);
    }

//    cout << "Функция вызвана: " << calledTimes << " раз" << endl;
    printSolution(savedSquares);
}

void Solution::printSolution(vector<Square> &obj) const {
    cout << minCount << endl;
    for(auto & i : obj)
        cout << i.x*gcd  + 1 << " " << i.y*gcd + 1 << " " << i.size*gcd  << endl;
}

void Solution::saveSolution() {
    savedSquares.clear();
    savedSquares.assign(squares.begin(), squares.end());
}

void Solution::setSquare(Square &info) {
    for(int i = 0; i != info.size; i++){
        for(int j = 0; j != info.size; j++)
            (*map)[info.y + i][info.x + j] = info.size;
    }
}

void Solution::deleteSquare(Square &info) {
    for(int i = 0; i != info.size; i++){
        for(int j = 0; j != info.size; j++)
            (*map)[info.y + i][info.x + j] = 0;
    }
}

void Solution::fillArea(int depth) {
    if(depth + 1 >= minCount){
//        printIndent(depth); cout << "There is no sense to go farther. depth:"<< depth << ", width:" << minCount << endl;
        return;
    }
    Square opportunity{};
    calledTimes++;
    opportunity = findOpportunity(0, fixedSize / 2, fixedSize / 2);
//    cout << opportunity.x << " " << opportunity.y << " " << opportunity.size << endl;
//
//
//    printIndent(depth); cout << "Put at (" << opportunity.y << "," << opportunity.x <<
//                             "), side size: " << opportunity.size << ", depth: " << depth <<
//                             ", current result: "<< squares.size() << endl;

    for(int i = opportunity.size; i > 0; i--) {
        opportunity.size = i;
        setSquare(opportunity);
        squares.push_back(opportunity);
//        printMap(depth);
        if(isFreeArea(0, fixedSize / 2, fixedSize/2 + 1)) {
            fillArea(depth + 1);
        }
        else{
            if(depth + 1 < minCount){
                minCount = depth + 1;
                saveSolution();
//                printIndent(depth); cout << "Got solution: "<< minCount << endl;
            }
            deleteSquare(opportunity);
            squares.pop_back();
            return;
        }
//        printIndent(depth); cout << "Recursion return, current depth:  " << depth << endl;
        deleteSquare(opportunity);
        squares.pop_back();

//        printIndent(depth); cout << "Remove square " << squares.back().size <<" from (" << squares.back().y << ", " << squares.back().x << ")" <<endl;
    }
}

void Solution::fillAreaIter(int x, int y) {
    stack<Square> stack;
    Square opportunity{};
    do {
        calledTimes++;
        int sz = (int) stack.size() + alreadySetCount;
        bool isFreePlace = isFreeArea(x, y, fixedSize/2+1);
        if ((sz >= minCount) || (!isFreePlace)) {
            if (!isFreePlace) {
                if (sz < minCount) {
                    minCount = sz;
//                    cout << "Сохранить\n";
//                    printMap(sz);
                    saveSolution();
//                    printSolution(savedSquares);
                }
            }

            while (!stack.empty()) {
                opportunity = stack.top();
//                cout << "Привет\n" << opportunity.y << " " << opportunity.x << " " << opportunity.size <<  endl;

                if (opportunity.size == 1) { // если квадрат имеет сторону 1, то полностью удалить
                    deleteSquare(opportunity);
                    squares.pop_back();
                    stack.pop();

//                    cout << stack.size() << "++ " << squares.size() << endl;
//                    printSolution(squares);
//                    printMap(sz);
                } else { // иначе уменьшить размер его стороны на 1 и отразить это на карте, после чего прекратить цикл
                    deleteSquare(opportunity);
                    opportunity.size--;
                    squares.back().size--;
                    stack.top().size = opportunity.size;
                    setSquare(opportunity);
//                    printMap(sz); cout << endl;
                    break;
                }
            }
            continue; // если после этого перебора стек оказывается пуст, то конец
        }

        opportunity = findOpportunity(x, y, fixedSize / 2);
        stack.push(opportunity);
        setSquare(opportunity);
        squares.push_back(opportunity);
//                    printMap(squares.size()); cout << endl;
//        cout << "Запушил \n" << opportunity.y << " " << opportunity.x << " " << opportunity.size <<  endl;
    }while(!stack.empty());
//    cout << "Цикл запущен " << calledTimes << endl;
}

bool Solution::isFreeArea(int x, int y, int range) {
    for(int i = y; i < y + range; i++){
        for(int j = x; j < x + range; j++){
            if((*map)[i][j] == 0) {
                return true;
            }
        }
    }
    return false;
}

Square Solution::findOpportunity(int xFrom, int yFrom, int maxLen) {
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

Square Solution::getSquare(int x, int y, int currentSize) {
    auto & refMap = (*map);
    int futSize =  currentSize;
    if(x + futSize > fixedSize) return {-1, -1, 0};
    if(y + futSize > fixedSize) return {-1, -1, 0};
//    cout << futSize << endl;

    for (int i = y; i < y + futSize; i++) {
        for (int j = x; j < x +  futSize; j++) {
            if (refMap[i][j] != 0){
                return {-1, -1, 0};
            }
        }
    }

    return {x, y, futSize};
}

void Solution::printIndent(int n) {
    for(int i = 0; i < n; i++) cout << "\t";
}



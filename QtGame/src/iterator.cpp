#include "../inc/Iterator.h"

Iterator::Iterator(Cell **map, int width, int height):map(map), width(width), height(height){}


Cell & Iterator::current() {
    if((iterRowCounter < height) && (iterColCounter < width) && (iterRowCounter >= 0) && (iterColCounter >= 0))
        return map[iterRowCounter][iterColCounter];
    else {
        return map[height - 1][width - 1];
    }
}

void Iterator::next() {
    if(containerOver){
        return ;
    }

    if(iterColCounter < width) iterColCounter++;
    else {
        if(iterRowCounter == height-1){
            containerOver = true;
            iterColCounter = 0;
            iterRowCounter = 0;
            return;
        }
        iterColCounter = 0;
        iterRowCounter++;
    }

}

void Iterator::first() {
    iterColCounter = 0;
    iterRowCounter = 0;
}

bool Iterator::isDone() const {
    return containerOver;
}

bool Iterator::rowEnd() const {
    return iterColCounter == (width);
}

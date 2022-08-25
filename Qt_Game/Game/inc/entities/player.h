#ifndef PLAYER_H
#define PLAYER_H
#include "../cell.h"
#include "../allclasses.h"

enum Direction{
    UP,
    DOWN,
    RIGHT,
    LEFT
};

class Player
{
public:
    Player(int x, int y);
    ~Player();
    int getHitpoints();
    int getScore();
    void addScore();
    void minusHp();
    void plusHp();
    bool dead();
    int & getX();
    int & getY();
    int & getPrevX();
    int & getPrevY();
    Direction & getDirection();
    Player & operator+=(IElement & element);
private:
    int hitpoints = 1;
    int score = 0;
    int x;
    int y;
    int prevX;
    int prevY;
    Direction direction = RIGHT;

};

#endif // PLAYER_H

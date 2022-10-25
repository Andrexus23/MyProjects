#include "../../inc/entities/player.h"
#include "../../inc/entities/ielement.h"
Player::Player(int x, int y):x(x), y(y){}

Player::~Player()
{

}

int Player::getHitpoints()
{
    return hitpoints;
}

int Player::getScore()
{
    return score;
}

void Player::addScore()
{
    score++;
}

void Player::minusHp()
{
    hitpoints--;
}

void Player::plusHp()
{
    hitpoints++;
}

bool Player::dead()
{
    return hitpoints <= 0;
}

int &Player::getX()
{
    return x;
}

int &Player::getY()
{
    return y;
}

int &Player::getPrevX()
{
    return prevX;
}

int &Player::getPrevY()
{
    return prevY;
}

Direction &Player::getDirection()
{
    return direction;
}

Player &Player::operator+=(IElement &element)
{
    element.changeScore(this);
    element.changeLives(this);
    return *this;
}

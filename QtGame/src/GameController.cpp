#include "../inc/GameController.h"
#include "../inc/map.h"

GameController::GameController()
{
    player = new Player(0, 0);
    entities = nullptr;
    sizeEntities = 0;
    generateMaze();
    generateEntities(3, 3, 3);
//    map.printMap();
    map.initMap(player, entities, sizeEntities);
}

GameController::~GameController()
{
    for(int i = 0; i < sizeEntities; i++)
        delete entities[i];
    delete [] entities;

    delete player;
}

IElement * GameController::deleteEntity(IElement *el)
{
    qDebug() << "delete Entity()";
    if(sizeEntities == 0) return nullptr;
    bool FOUND = false;
    for(int i = 0; i < sizeEntities; i++){
        if(entities[i] == el){
            delete entities[i];
            entities[i] = nullptr;
            FOUND = true;
            break;
        }
    }
    if(!FOUND) return nullptr;

    IElement ** newEntities = new IElement*[sizeEntities-1];
    int newI = 0;
    for(int i = 0; i < sizeEntities; i++){
        if(entities[i] != nullptr){
            newEntities[newI] = entities[i];
            newI++;
        }
    }
    sizeEntities--;
    delete [] entities;
    entities = newEntities;
    return el;
}

IElement * GameController::addEntity(IElement *el)
{
//     qDebug() << "add Entity()";
    IElement ** newEntities = new IElement*[sizeEntities+1];
    for(int  i = 0; i < sizeEntities; i++){
        newEntities[i] = entities[i];
    }
    delete [] entities;
    sizeEntities++;
    newEntities[sizeEntities-1] = el;
    entities = newEntities;
    return el;
}

void GameController::printEntities()
{
    qDebug() << sizeEntities;
    for(int i = 0; i < sizeEntities; i++){
        switch (entities[i]->getClass()) {
            case BOMB:
                qDebug() << "BOMB: " << entities[i]->getX() << " " << entities[i]->getY();
                break;
            case COIN:
                qDebug() << "COIN: " << entities[i]->getX() << " " << entities[i]->getY();
                break;
            case HITPOINT:
                qDebug() << "HITPOINT: " << entities[i]->getX() << " " << entities[i]->getY();
                break;
            default:

                break;
        }
    }
}

CellStatus GameController::whatInCell(int x, int y)
{
    return map.whatInCell(x, y);
}



void GameController::moveUp()
{
    if((player->getY() > 0) && (map.whatInCell(player->getX(), player->getY() - 1) != WALL) && player->getDirection() == UP) {
        player->getY()--;
    }
    player->getDirection() = UP;
    playerMoved = true;
}

void GameController::moveDown()
{
//    qDebug() << "moving down";
    if((player->getY() < map.getHeight() - 1) && (map.whatInCell(player->getX(), player->getY() + 1) != WALL) && player->getDirection() == DOWN)
    {
        player->getY()++;
    };
     player->getDirection() = DOWN;
     playerMoved = true;
}

void GameController::moveRight()
{
    if((player->getX() < map.getWidth()-1) && (map.whatInCell(player->getX() + 1, player->getY()) != WALL) && player->getDirection() == RIGHT)
    {
        player->getX()++;

    }
    player->getDirection() = RIGHT;
    playerMoved = true;
}

void GameController::moveLeft()
{

     if((player->getX() > 0) && (map.whatInCell(player->getX() - 1, player->getY()) != WALL)&& player->getDirection() == LEFT)
     {
         player->getX()--;

     }
     player->getDirection() = LEFT;
     playerMoved = true;
}

void GameController::update()
{
    IElement * onWay = nullptr;
    if(map.whatInCell(player->getX(), player->getY()) != EMPTY){
        for(int i = 0; i < sizeEntities; i++){ // взаимодействие с элементом поля
            if((entities[i]->getX() == player->getX()) &&
                    (entities[i]->getY() == player->getY())){
                onWay = entities[i];
                (*player) += (*entities[i]);
                qDebug() << "Player vs " << entities[i]->getClass() << "Player: hp: " << player->getHitpoints() <<
                          "score: " << player->getScore() << " " << entities[i]->getClass() << ": " << entities[i]->isAvailable();
                break;
            }
         }
    }
    if(onWay != nullptr){
        if(!(onWay->isAvailable())){
            map.deleteEntity(onWay->getX(), onWay->getY());
            deleteEntity(onWay);
        }
    }
     map.update();
     if(player->dead()) {
         gameOver = true;
         map.deleteEntity(player->getX(), player->getY());

     }
}

void GameController::generateMaze()
{

    while(!(map.isValidMaze())){
            map.genMaze();
    }
}

void GameController::checkEntityCollision(int & newX, int & newY)
{

    AGAIN:
    for(int j = 0; j < sizeEntities; j++){

        if(((entities[j]->getX() == newX)  && (entities[j]->getY() == newY)) || (map.whatInCell(newX, newY) == WALL) || ((newX == player->getX()) && (newY == player->getY()))){
            while(((entities[j]->getX() == newX)  && (entities[j]->getY() == newY)) || (map.whatInCell(newX, newY) == WALL) || ((newX == player->getX()) && (newY == player->getY()))){
                newX = rand() % MAPWIDTH;
                newY = rand() % MAPHEIGHT;
            }
            goto AGAIN;
        }
    }
    if(map.whatInCell(newX, newY) == WALL){
        newX = rand() % MAPWIDTH;
        newY = rand() % MAPHEIGHT;
        goto AGAIN;
    }
}

void GameController::generateEntities(int nBombs, int nHits, int nCoins)
{
    int newX = rand() % MAPWIDTH;
    int newY = rand() % MAPHEIGHT;

    for(int i = 0; i < nBombs; i++){
        checkEntityCollision(newX, newY);
        qDebug() << newX << " " << newY << "Status: " << map.whatInCell(newX, newY);
        addEntity(new Bomb(newX, newY));

    }

    for(int i = 0; i < nHits; i++){
        checkEntityCollision(newX, newY);
        qDebug() << newX << " " << newY << "Status: " << map.whatInCell(newX, newY);
        addEntity(new Hitpoint(newX, newY));

    }

    for(int i = 0; i < nCoins; i++){
        checkEntityCollision(newX, newY);
        qDebug() << newX << " " << newY << "Status: " << map.whatInCell(newX, newY);
        addEntity(new Coin(newX, newY));
    }

}

bool GameController::someThingChanged()
{
//    qDebug() << player->getX() << " " << player->getY() << " " << playerMoved;
    if(playerMoved){
        playerMoved = false;
        return true;
    }
    return false;
}

bool GameController::cellChanged(int x, int y)
{
    return map.cellChanged(x, y);
}

Player *GameController::getPlayer()
{
    return player;
}

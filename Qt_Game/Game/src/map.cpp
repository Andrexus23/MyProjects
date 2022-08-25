#include "../inc/map.h"
#include "QDebug"

Map::Map(int width, int height):width(width), height(height)
{
    if(width <= 0) this->width = 1;
    if(height <= 0) this->height = 1;
    map = new Cell*[this->height];
    for(int i = 0; i < this->height; i++){
        map[i] = new Cell[this->width];
        for(int j = 0; j < this->width; j++){
            map[i][j].getStatus() = WALL;
        }
    }

    srand(time(nullptr));
    tractors.resize(5);
}

//Map::Map(const Map &obj):width(obj.width), height(obj.height) // конструктор копирования
//{
//    this->map = new Cell*[height];
//    for(int i = 0; i < height; i++){
//        this->map[i] = new Cell[width];
//        for(int j = 0; j < width; j++){
//            this->map[i][j].getStatus() = obj.map[i][j].getStatus();
//        }
//    }
//}

//Map::Map(Map && obj) // конструктор перемещения
//{
//    swap(obj);
//}

Map &Map::instance()
{
    static Map map(MAPWIDTH, MAPHEIGHT);
    return map;
}

Map::~Map()
{
    for(int i = 0; i < height; i++)
        delete [] map[i];
    delete [] map;
}

//Map &Map::operator =(const Map &obj) // оператор присваивания
//{
//    if(this != &obj){ // если мы не присваиваем объект самому себе
//        Map(obj).swap(*this); // создаём копию объекта и присваиваем
//    }
//    return *this;
//}

//Map &Map::operator = (Map && obj) // оператор перемещения
//{
//    swap(obj);
//    return *this;
//}



void Map::swap(Map &obj)
{
    std::swap(this->map, obj.map);
    std::swap(this->width, obj.width);
    std::swap(this->height, obj.height);
}

void Map::printMap()
{
    if(this->map != nullptr) {
        Iterator * iter = createIterator();
            for(iter->first(); !iter->isDone(); iter->next()){
                if(!iter->rowEnd()) cout << iter->current().getStatus();
                else cout << std::endl;
            }
        delete iter;
    }
}

int Map::getWidth()
{
    return width;
}

int Map::getHeight()
{
    return height;
}

void Map::initMap(Player *player, IElement **entities, int sizeEntities)
{
    this->player = player;
    if(player->getX() >= 0 && player->getY() >= 0 && player->getX() < width && player->getY() < height)
        map[player->getY()][player->getX()].getStatus() = PLAYER;
    for(int i = 0; i < sizeEntities; i++){
        if(entities[i]->getX() >= 0 &&
                entities[i]->getY() >= 0 &&
                entities[i]->getX() < width &&
                entities[i]->getY() < height){
            map[entities[i]->getY()][entities[i]->getX()].getStatus() = entities[i]->getClass();
        }
    }
}

void Map::update()
{
     if(player->getX() >= 0 && player->getY() >= 0 && player->getX() < width && player->getY() < height){
         CellStatus s = map[playerY][playerX].getStatus();
         map[playerY][playerX].getPrevStatus() = s;
//         qDebug() << playerY << " " << playerX << " " <<  map[playerY][playerX].getPrevStatus();
         map[playerY][playerX].getStatus() = before;
         playerY = player->getY();
         playerX = player->getX();
//         qDebug() << playerY << " " << playerX << " " <<  map[playerY][playerX].getStatus();
         s = map[playerY][playerX].getStatus();
         map[playerY][playerX].getPrevStatus() = s;
         before = map[playerY][playerX].getStatus();
         map[playerY][playerX].getStatus() = PLAYER;

//         qDebug() << map[playerY][playerX].getPrevStatus()  << " " <<  map[playerY][playerX].getStatus();
     }
}

CellStatus Map::whatInCell(int x, int y)
{
    return map[y][x].getStatus();
}


Iterator *Map::createIterator()
{
    return new Iterator(map, width, height);
}

void Map::deleteEntity(int x, int y)
{
    map[y][x].getPrevStatus() = map[y][x].getStatus();
    map[y][x].getStatus() = EMPTY;
}

bool Map::cellChanged(int x, int y)
{
    return map[y][x].getStatus() != map[y][x].getPrevStatus();
}

void Map::genMaze()
{
    for(auto & t : tractors) moveTractor(t);
}

void Map::moveTractor(Tractor & tractor)
{
    vector<pair<int, int>> directions;
        if(tractor.x > 1){ // движение влево
            directions.emplace_back(-2, 0);
        }

        if(tractor.x < (width - 2)){ // движение вправо
            directions.emplace_back(2, 0);
        }

        if(tractor.y > 1){
            directions.emplace_back(0, -2);
        }

        if(tractor.y < (height - 2)){
            directions.emplace_back(0, 2);
        }
        pair<int, int>  direction = getRandomItem(directions);

        tractor.x += direction.first;
        tractor.y += direction.second;

        if(map[tractor.y][tractor.x].getStatus() != EMPTY) {
            map[tractor.y][tractor.x].getStatus() = EMPTY;
            map[tractor.y - direction.second/2][tractor.x - direction.first/2].getStatus() = EMPTY;
            map[tractor.y - direction.second][tractor.x - direction.first].getStatus() = EMPTY;
        }

}

pair<int, int> Map::getRandomItem(vector<pair<int, int> > &directions)
{
    int index = rand() % (directions.size());
//    cout << index << endl;
    return directions.at(index);
}

bool Map::isValidMaze()
{
    for(int i = 0; i < height; i+=2){
        for(int j = 0; j < width; j+=2){
            if((map[i][j].getStatus()) == WALL) return false;
        }
    }
    return true;
}

#ifndef MAP_H
#define MAP_H
#include "cell.h"
#include "Iterator.h"
#include "./entities/ielement.h"
#include "vector"

#define MAPWIDTH 31
#define MAPHEIGHT 15
#define TRACTORSCOUNT 5

struct Tractor{
    int x = 0;
    int y = 0;
};

class Map
{
public:
    static Map & instance();
    ~Map();
    void printMap();
    int getWidth();
    int getHeight();
    void initMap(Player * player, IElement ** entities, int sizeEntities);
    void update();
    CellStatus  whatInCell(int x, int y);
    Iterator * createIterator();
    void deleteEntity(int x, int y);
    bool cellChanged(int x, int y);
    void genMaze();
    void moveTractor(Tractor & tractor);
    pair<int, int> getRandomItem(vector<pair<int, int>> &directions);
    bool isValidMaze();
private: // для реализации синглтона все конструкторы надо сделать приватными, оператор копирования и присваивания тоже.
    Map(int width, int height);
    Map() : Map(1, 1) {};
    // объявим, но не определим конструктор копирования и оператор присваивания для синглтона
    Map(const Map & obj); // конструктор копирования - создаёт новый объект и копирует данные
    Map(Map && obj); // конструктор перемещения - отбирает данные у объекта (меняет местами)
    Map & operator = (Map const& obj); // оператор присваивания
    Map & operator = (Map && obj); // оператор перемещения
    Cell** map = nullptr;
    void swap(Map & obj);
    int width = 0;
    int height = 0;
    int playerX = 0;
    int playerY = 0;
    vector<Tractor> tractors;
    Player * player;
    CellStatus before = EMPTY;
    friend class Iterator;
    friend class MapView;
};

#endif // MAP_H

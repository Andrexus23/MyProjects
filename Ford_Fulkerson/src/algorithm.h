#ifndef FORD_FULKERSON_ALGORITHM_H
#define FORD_FULKERSON_ALGORITHM_H
#include <iostream>
#include <vector>
#include <list>
#include "ostream"
#include "map"
#include "string"
#include "algorithm"
#define DEBUG 1
using namespace std;
struct edge{
    long first{};
    long second{};
    bool reverse = false;
    bool enabled = true;
};

struct Vertex{
    char id; // название вершины
    pair<long, char> labelFrom = {INT64_MAX, '-'}; // метка
    bool marked = false; // флаг того, помечен ли узел или нет
    vector<char> canGo; // S_i как множество узлов, в которые можно перейти из узла по ребру с с_ij > 0 для всех j, принадлежащих S_i
    map<char, edge> adjList; // список инцидентных рёбер
    map<char, edge> adjListRev;
};

struct edgeForRes{
    char from;
    char to;
    long capacity;
};

struct cmpFirst{
    bool operator ()(const edgeForRes& first, const edgeForRes& second){
        return first.from < second.from;
    }
};

struct cmpSecond{
    bool operator ()(const edgeForRes& first, const edgeForRes& second){
        return first.to < second.to;
    }
};

struct cmpAlpha{
    bool operator ()(const char& first, const char& second){
        return first < second;
    }
};

struct Graph{
    map<char, Vertex> graph;
    map<char, Vertex> copyGraph;
    vector<edgeForRes> answer;
    long maxFlow = 0;
    char srcId;
    char destId;
    char currentVertex;
    int edgesCount;
};

void inputFile(Graph &graphObj, string &path);
void maxFlowAlgo(Graph &graphObj);
void printGraph(map<char, Vertex> &graphObj);
void printResult(Graph &graph);
int step_2(Graph &graphObj);
int step_3(Graph &graphObj);
int step_4(Graph &graphObj);
int step_5(Graph &graphObj);
int step_6(Graph &graphObj);



#endif //FORD_FULKERSON_ALGORITHM_H

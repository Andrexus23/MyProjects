// Сложность по времени O(E*F), E - число рёбер в сети, F - максимальный поток в сети 

#include <iostream>
#include <vector>
#include <list>
#include "ostream"
#include "map"
#include "string"
#include "algorithm"
#define DEBUG 0
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

void inputFile(Graph &graphObj, string &path) {
   // std::ifstream  in;
    char from, to;
    long capacity;
    //in.open(path, ios::app|ios::out|ios::in|ios::binary);
    cin >> graphObj.edgesCount;
    cin >> graphObj.srcId;
    cin >> graphObj.destId;

    for(int i = 0; i < graphObj.edgesCount; i++){
        cin >> from >> to >> capacity;

        graphObj.graph[from].id = from;
        graphObj.copyGraph[from].id = from;

        graphObj.graph[to].id = to;
        graphObj.copyGraph[to].id = to;

            graphObj.graph[from].adjList[to].first = capacity;
            graphObj.graph[from].adjList[to].second = 0;
            if(from == graphObj.destId){
                graphObj.graph[from].adjList[to].enabled = false;
            }

            graphObj.graph[to].adjListRev[from].first = 0;
            graphObj.graph[to].adjListRev[from].second = capacity;
            graphObj.graph[to].adjListRev[from].reverse = true;

            if(to == graphObj.srcId)  graphObj.graph[to].adjListRev[from].enabled = false;

            graphObj.copyGraph[from].adjList[to].first = capacity;
            graphObj.copyGraph[from].adjList[to].second = 0;
            if(from == graphObj.destId)  graphObj.copyGraph[from].adjList[to].enabled = false;

    }

    graphObj.graph[graphObj.srcId].id = graphObj.srcId;
    graphObj.graph[graphObj.destId].id = graphObj.destId;

    graphObj.copyGraph[graphObj.srcId].id = graphObj.srcId;
    graphObj.copyGraph[graphObj.destId].id = graphObj.destId;
}

void maxFlowAlgo(Graph &graphObj){
    // инициализация
    graphObj.graph[graphObj.srcId].labelFrom = {INT64_MAX, '-'};
    graphObj.graph[graphObj.srcId].marked = true;
    graphObj.currentVertex = graphObj.srcId;

    int state = step_2(graphObj);
    while(state != -1){
        switch (state) {
            case 2:
                state = step_2(graphObj);
                break;
            case 3:
                state = step_3(graphObj);
                break;
            case 4:
                state = step_4(graphObj);
                break;
            case 5:
                state = step_5(graphObj);
                break;
            case 6:
                state = step_6(graphObj);
                break;
            default:
                break;
        }
    }

}



int step_2(Graph &graphObj){
    /* определяем множество S_i как множество узлов, в которые можно перейти из узла i
     * по ребру с с_ij > 0 для всех j, принадлежащих S_i
     * */
    for(auto & i : graphObj.graph[graphObj.currentVertex].adjList){
        if((i.second.first > 0)  && !(graphObj.graph[i.first].marked) && i.second.enabled){ // пропускная способность > 0 и узел непомечен на данной итерации и ребро действующее
            graphObj.graph[graphObj.currentVertex].canGo.push_back(i.first);
        }
    }

    for(auto & i : graphObj.graph[graphObj.currentVertex].adjListRev){
        if((i.second.first > 0)  && !(graphObj.graph[i.first].marked) && i.second.enabled){ // пропускная способность > 0 и узел непомечен на данной итерации и ребро действующее
            graphObj.graph[graphObj.currentVertex].canGo.push_back(i.first);
        }
    }


    if(graphObj.graph[graphObj.currentVertex].canGo.empty()){
        if(DEBUG) cout << "Список смежности пуст\n";
        return 4; // -> 4
    }
    else {
        return 3; // -> 3
    }
}

int step_3(Graph &graphObj){
    // во множестве S_i находим узел k: с_ik = max{c_ij} для всех j, принадлежащих S_i
    long minC = INT64_MAX;
    char nextId;
    vector<char>::iterator  t;

    sort(graphObj.graph[graphObj.currentVertex].canGo.begin(), graphObj.graph[graphObj.currentVertex].canGo.end(), cmpAlpha());
    /*if( ((t = find(graphObj.graph[graphObj.currentVertex].canGo.begin(),
            graphObj.graph[graphObj.currentVertex].canGo.end(),
            graphObj.destId)) != graphObj.graph[graphObj.currentVertex].canGo.end()) &&
            ){
    } */

    if(DEBUG) {
        cout << "Список смежности вершины " << graphObj.currentVertex << ":[" ;
        for(auto & i : graphObj.graph[graphObj.currentVertex].canGo){
            cout << i << ", ";
        }
        cout << "]\n";
    }

    for(auto i: graphObj.graph[graphObj.currentVertex].canGo)
    {
        if(graphObj.graph[graphObj.currentVertex].adjListRev.find(i) != graphObj.graph[graphObj.currentVertex].adjListRev.end()){
            /*if (graphObj.graph[graphObj.currentVertex].adjListRev[i].first > minC) {
                minC = graphObj.graph[graphObj.currentVertex].adjListRev[i].first;
                nextId = i;
            } */
            if (graphObj.graph[graphObj.currentVertex].adjListRev[i].enabled &&
                    graphObj.graph[graphObj.currentVertex].adjListRev[i].first > 0 &&
                graphObj.graph[graphObj.currentVertex].adjListRev[i].first < minC) {
                minC = graphObj.graph[graphObj.currentVertex].adjListRev[i].first;
                nextId = i;
                break;
            }
            else goto other_way;
        } else if(graphObj.graph[graphObj.currentVertex].adjList.find(i) != graphObj.graph[graphObj.currentVertex].adjList.end()) {
            other_way:
            if(graphObj.graph[graphObj.currentVertex].adjList[i].enabled &&
                    graphObj.graph[graphObj.currentVertex].adjList[i].first > 0 &&
               graphObj.graph[graphObj.currentVertex].adjList[i].first <= minC){
                minC = graphObj.graph[graphObj.currentVertex].adjList[i].first;
                nextId = i;
            }
        }



    }

    if(DEBUG) {
        cout << "Переход по ребру " << graphObj.currentVertex <<
             " --> " << nextId << " [" << minC << "]\n";
    }
    // положим a_k = c_ik  и пометим узел k меткой [a_k, i]
    //cout << "Метка для " << nextId << ": " << minC << " " <<graphObj.currentVertex << endl;
    graphObj.graph[nextId].labelFrom = {minC, graphObj.currentVertex};
    graphObj.graph[nextId].marked = true;

    graphObj.currentVertex = nextId;

    if(nextId == graphObj.destId) {
        //cout << " -> " << graphObj.currentVertex << " (" << graphObj.graph[graphObj.currentVertex].labelFrom.first
          //   << "," << graphObj.graph[graphObj.currentVertex].labelFrom.second << ")";
        return 5;
    }
    else {
      //  cout << " -> " << graphObj.currentVertex << " (" << graphObj.graph[graphObj.currentVertex].labelFrom.first
            // << "," << graphObj.graph[graphObj.currentVertex].labelFrom.second << ")";
        return 2;
    }

}

int step_4(Graph &graphObj){ // откат назад
    if(graphObj.currentVertex == graphObj.srcId){ // если текущий при этом шаге равен истоку, то сквозной путь невозможен и мы переходим к шагу 6
       if(DEBUG) {
           cout << "Бежать больше некуда\n";
       }
       return 6; // -> 6
    } else{
        char prevId = graphObj.graph[graphObj.currentVertex].labelFrom.second;
        Vertex & previous = graphObj.graph[prevId];
        std::map<char, edge>::iterator it;
        it = previous.adjList.find(graphObj.currentVertex);
        if(it == previous.adjList.end() || (it->second.enabled == false)){
            it = previous.adjListRev.find(graphObj.currentVertex);
        }
        it->second.enabled = false;
        graphObj.graph[graphObj.currentVertex].marked = false; // ???
        if(DEBUG){
            cout << "ОТКАТ. Убрали вершину " << graphObj.currentVertex << " из списка смежности "
            << previous.id << endl;
        }

        graphObj.currentVertex = previous.id;

        graphObj.graph[graphObj.currentVertex].canGo.clear();
        return 2;
    }
}

int step_5(Graph &graphObj){
    long minP = graphObj.graph[graphObj.currentVertex].labelFrom.first;
    Vertex * current = &(graphObj.graph[graphObj.currentVertex]);
    // считаем максимальный поток
    while(current->id != graphObj.srcId){
        if(current->labelFrom.first < minP){
            minP = current->labelFrom.first;
        }
       current = &(graphObj.graph[current->labelFrom.second]); // возвращаемся назад ища максимальный поток
    }
    // обновляем пропускные способности
    if(DEBUG){
        cout << "Макс. поток на данном сквозном пути: "<< minP << "\n\n";
    }

    current = &(graphObj.graph[graphObj.currentVertex]);
    while(current->id != graphObj.srcId){
        // изменяем текущие остаточные стоимости
        Vertex & previous = graphObj.graph[current->labelFrom.second];
        if(previous.adjList.find(current->id) != previous.adjList.end()) { // если перешли по прямому ребру
            previous.adjList[current->id].first -= minP;
            previous.adjList[current->id].second += minP;

            current->adjListRev[previous.id].first += minP;
            current->adjListRev[previous.id].second -= minP;
        }
        else { // если по обратному
            previous.adjListRev[current->id].first -= minP;
            previous.adjListRev[current->id].second += minP;

            current->adjList[previous.id].first += minP;
            current->adjList[previous.id].second -= minP;
        }



        // убираем метку с текущего узла пути
        char curTemp = current->labelFrom.second;
        current->labelFrom = {INT64_MAX, '-'};
        current->marked = false;

        // обнуляем списки id вершин, в которые можно перейти из текущей
        current->canGo.clear();
        // переходим на предыдущий узел пути и делаем с ним то же самое
        current = &(graphObj.graph[curTemp]);
    }
    if(DEBUG){
        printGraph(graphObj.graph);
    }
    // убрали метки со всех узлов кроме истока
    //  вернулись на первый (второй) шаг для поиска нового сквозного пути
    graphObj.currentVertex = graphObj.srcId;
    graphObj.graph[graphObj.currentVertex].canGo.clear();

    graphObj.maxFlow += minP;
   // cout << "minP= " << minP << endl;
    return 2;
}

int step_6(Graph &graphObj){
    for(auto & vertex: graphObj.copyGraph){
        for(auto & edge : vertex.second.adjList){
                edge.second.first -= graphObj.graph[vertex.first].adjList[edge.first].first;
                edge.second.second -= graphObj.graph[vertex.first].adjList[edge.first].second;
        }
    }
    return -1;
}
void printGraph(map<char, Vertex> &graph){
    for(auto & i : graph){
        cout << i.first << ":\n";
        for(auto & j : i.second.adjList){
            cout << "\t" << j.first << ": (" << j.second.first << "," << j.second.second << "," << j.second.enabled <<"," << j.second.reverse << ");" << endl;
        }
    }
}

void printResult(Graph &graph){
    for(auto & el: graph.copyGraph){
        for(auto & edge : el.second.adjList){
            graph.answer.push_back({el.first, edge.first, edge.second.first >= 0 ? edge.second.first : edge.second.second});
        }
    }

    std::sort(graph.answer.begin(), graph.answer.end(), cmpSecond());
    std::sort(graph.answer.begin(), graph.answer.end(), cmpFirst());


    cout << graph.maxFlow << endl;
    for(auto & i: graph.answer){
        cout << i.from << " " << i.to << " " << i.capacity << endl;
    }
}


int main(int argc, char ** argv) {
    Graph graph;
    string path ="/home/andrey/CLionProjects/Ford_Fulkerson/test1";
    inputFile(graph, path);
    maxFlowAlgo(graph);
    //cout << endl;
    //printGraph(graph.graph);
    //cout << endl;
   // printGraph(graph.graph);
    printResult(graph);
    return 0;
}
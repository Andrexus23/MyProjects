#include "algorithm.h"

int main(int argc, char ** argv) {
    Graph graph;
    string path ="/home/andrey/CLionProjects/Ford_Fulkerson/test12";
    inputFile(graph, path);
    maxFlowAlgo(graph);
    //cout << endl;
    //printGraph(graph.graph);
    //cout << endl;
   // printGraph(graph.graph);
    printResult(graph);
    return 0;
}

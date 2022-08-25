#include <iostream>
#include "vector"
#include "algorithm"
#include "limits"
#include "cmath"
#include "queue"
#include "map"

using namespace std;

struct Vertex{
    float g = (float)INT64_MAX;
    float f = (float)INT64_MAX;
    char id = ' ';
};

struct Edge{
    char from;
    char to;
    float weight;
};

struct Compare{
public:
    bool operator () (Vertex & a, Vertex & b){
        return a.f >= b.f;
    }
};

class Logger{
public:
    static void log(string & str, const string& message){
        cout << message;
        cout << str << "\n\n";
    };

    static void log(map<char, char> & v){
        for(auto & item : v){
            cout << item.first << " " << item.second <<  endl;
        }
        cout << endl;
    };

    static void log(vector<Vertex> & v){
        for(auto & item : v){
            cout << "id: " << item.id << ", g[" << item.id << "]: " << item.g <<", f[" << item.id << "]: " << item.f << endl;
        }
        cout << endl;
    };
};

class Solution{
public:
    Solution(){
        string line;
        Edge edge;
        getline(cin, line);
        from = line[0]; to = line[2];
        while(getline(cin, line)){
            if(line.empty()){
                break;
            }
            edge.from = line[0];
            edge.to = line[2];
            if(vertexesString.find(edge.from) == string::npos) vertexesString += edge.from;
            if(vertexesString.find(edge.to) == string::npos) vertexesString += edge.to;
            edge.weight = atof(line.substr(4, line.size()).c_str());
            graph.push_back(edge);
        }
//        std::sort(vertexesString.begin(), vertexesString.end());
//        cout << vertexesString << endl;
//        Logger::log(vertexesString, "Vertexes: ");
        astar();
    }

    void astar(){
        Vertex v{}; v.g = 0; v.f = v.g + h(from, to); v.id = from;
        queue.push(v);
        Vertex current{};
        vertexes.push_back(v);
        chain[from] = '-';
        inQueue += from;
        vertexes.resize(vertexesString.size());
        for(int i = 1; i < vertexes.size(); i++){
            vertexes[i].id = vertexesString[i];
        }

//       Logger::log(vertexes);
        while(!queue.empty()){
//           Logger::log(inQueue, "In queue: ");
//           Logger::log(vertexes);

            current = queue.top();
//            cout << "Current: " << current.id << endl;
            queue.pop();

            inQueue.erase(remove(inQueue.begin(), inQueue.end(), current.id), inQueue.end());

            if(current.id == to){
//               cout << "Решение найдено\n";
                float curSum = getVertexById(to).g;
                if(minSum >= curSum){
                    minSum = curSum;
                    saveSol();
                    break;
                }
            }
            closed += current.id;
            for(auto & edge: graph){
                if(edge.from == current.id){
                    Vertex & curRef = getVertexById(current.id);
                    Vertex & neighborRef = getVertexById(edge.to);
                    float tentativeScore = curRef.g + edge.weight;
                    if((closed.find(edge.to) != string::npos) && (tentativeScore >= neighborRef.g)){ // если содержится в списке просмотренных
                        continue;
                    }
                    if((closed.find(edge.to) == string::npos) || (tentativeScore < neighborRef.g)){
//                            cout << "tS: " << tentativeScore << ",  neighbor.g: " << neighborRef.g << endl;
                        if(tentativeScore < neighborRef.g) {
                            chain[neighborRef.id] = curRef.id;
                            neighborRef.g = tentativeScore;
                            neighborRef.f = (neighborRef.g + (float) h(neighborRef.id, to));
                            if (inQueue.find(neighborRef.id) == string::npos) {
                                inQueue += neighborRef.id;
                                queue.push(neighborRef);
                            }
                        }
                    }
                }
            }
        }
//        Logger::log(chain);
//        std::reverse(path.begin(), path.end());
        cout << path;
    }

    static int h(char a, char b){
        return (int) abs(a - b);
    }

    void saveSol(){
//        Logger::log(chain);
        char item = chain.at(to);
        path = to;
        while(item != '-'){
            path += item;
            item = chain[item];
        }
        std::reverse(path.begin(), path.end());
//        cout << path << endl;
    }

    void printInfo(){
        cout << from << " " << to << endl;
        for(auto & edge : graph){
            cout << edge.from << " " << edge.to << " " << edge.weight << endl;
        }
    };
    Vertex & getVertexById(char id){
        for(auto & v: vertexes){
            if(v.id == id)
                return v;
        }
    }
private:
    vector<Edge> graph;
    string closed;
    string path;
    map<char, char> chain;
    char from;
    char to;
    priority_queue<Vertex , vector<Vertex>, Compare> queue;
    vector<Vertex> vertexes;
    string vertexesString;
    string inQueue;
    float minSum = (float)INT64_MAX;
};

int main() {
    Solution sol;
//    cout << Solution::h('a', 'e');
    return 0;
}
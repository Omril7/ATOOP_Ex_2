//
// Graph.h
//

#ifndef EXERCISE_2_GRAPH_H
#define EXERCISE_2_GRAPH_H

#include "Ex2.h"
#include "Station.h"
#include <map>
#include <vector>
#include <list>
#include <iostream>
#include <cstring>
#include <memory>

template <class V>
class Graph {
private:
    vector<V> graph;   // maybe map<string,V> graph
//    vector<E> edges;
    string graphType;
    const int stop_t;
    Transit_time tt;

public:
    Graph(Transit_time t, string gt, int st) : tt(t), stop_t(st), graphType(gt) {}
    void printTT() const {
        std::cout << "intercity tt: " << tt.intercity << std::endl;
        std::cout << "centraal tt: " << tt.centraal << std::endl;
        std::cout << "stad tt: " << tt.stad << std::endl;
    }

    void addVertex(V v);
    void addEdge(V src, V dest, double w);
    bool containVertex(V v);
    bool containEdge(V src, V dest, double w);


    int getVertexIndex(string v);
    Graph<V> getReverse();

    void outBound(string src);               // [2]  V
    void inBound(string dest);               // [3]  V
    int uniExpress(string src, string dest);      // [4]
    int multiExpress(string src, string dest);    // [5]
    void print();                       // [6]  V

};

#endif //EXERCISE_2_GRAPH_H

//
// Graph.cpp
//

#include "Graph.h"

template <class V>
bool Graph<V>::containVertex(V v) {
    for(int i=0; i< static_cast<int>(graph.size()); i++) {
        if(graph[i].getName() == v) {
            return true;
        }
    }
    return false;
}
template <class V>
void Graph<V>::addVertex(V v) {
    if(!containVertex(v)) { // v is not in graph
        graph.push_back(v);
    }
}
template <class V>
bool Graph<V>::containEdge(V src, V dest, double w) {
    if(containVertex(src) && containVertex(dest)) {
        int i = getVertexIndex(src.getName());
        return graph[i].containEdge(dest, w);
    }
    return false;
}
template <class V>
void Graph<V>::addEdge(V src, V dest, double w) {
    if(!containEdge(src, dest, w)) {
        addVertex(src);
        addVertex(dest);
        int i = getVertexIndex(src.getName());
        graph[i].addEdge(dest, w);
    }
}

template <class V>
int Graph<V>::getVertexIndex(string v) {
    for(int i=0; i< static_cast<int>(graph.size()); i++) {
        if(graph[i].getName() == v) {
            return i;
        }
    }
    return -1;
}

template <class V>
void Graph<V>::outBound(string src) {
    cout << graphType << ": ";
    int count = 0;
    list<V> queue;
    graph[getVertexIndex(src)].changeVisit(true);
    queue.push_back(graph[getVertexIndex(src)]);
    while(!queue.empty()) {
        src = queue.front();
        queue.pop_front();
        for(auto adj : graph[getVertexIndex(src)].getAdj().getVertex()) {
            if(!adj.isVisited()) {
                count++;
                adj.changeVisit(true);
                cout << adj.getName() << '\t';
                queue.push_back(adj);
            }
        }
    }
    if(count == 0) {
        cout << "no outbound travel" << endl;
    }
    for(int i=0; i<static_cast<int>(graph.size()); i++) {
        graph[i].changeVisit(false);
    }
} // BFS
template <class V>
void Graph<V>::inBound(string dest) {
    Graph<V> revGraph = getReverse();

    cout << graphType << ": ";
    int count = 0;
    list<V> queue;
    revGraph[getVertexIndex(dest)].changeVisit(true);
    queue.push_back(revGraph[getVertexIndex(dest)]);
    while(!queue.empty()) {
        dest = queue.front();
        queue.pop_front();
        for(auto adj : revGraph[getVertexIndex(dest)].getAdj().getVertex()) {
            if(!adj.isVisited()) {
                count++;
                adj.changeVisit(true);
                cout << adj.getName() << '\t';
                queue.push_back(adj);
            }
        }
    }
    if(count == 0) {
        cout << "no outbound travel" << endl;
    }
    for(int i=0; i<static_cast<int>(graph.size()); i++) {
        graph[i].changeVisit(false);
    }
} // rev BFS
template <class V>
int Graph<V>::uniExpress(string src, string dest) {} // shortest path (Dijkstra)
template <class V>
int Graph<V>::multiExpress(string src, string dest) {} // shortest path (Dijkstra)
template<class V>
void Graph<V>::print() {
    cout << graphType << " graph: " << endl;
    for(int i=0; i<static_cast<int>(graph.size()); i++) {
        cout << '\t' << graph[i].getName() << " : " << graph[i].getAdj() << endl;
    }
}


// V needs V& operator=(const V& v) method
// E needs E& operator=(const E& e) method   -> maybe
// E needs V getVertex() const method
// V needs bool containEdge(V dest, double w) method
// V needs void addEdge(V dest, double w) method
// V needs void changeVisit(bool b) method
// V needs vector<E> getAdj() const method

// V needs bool isVisited() const method
// V needs string getName() const method

// E needs pointers to V in graph,
// because when we change in graph the V in E needs to adjust

//
// Created by Omri Leizerovitch on 05/07/2022.
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
    vector<V> graph;   // maybe map<V,E> graph
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

    void addVertex(const V& v);
    void addEdge(V src, V dest, int w);

    int getVertexIndex(string v);
    Graph<V> getReverse();

    void outBound(string src);               // [2]  V
    void inBound(string dest);               // [3]  V
    int uniExpress(string src, string dest);      // [4]
    int multiExpress(string src, string dest);    // [5]
    void print();                       // [6]  V

};

#endif //EXERCISE_2_GRAPH_H

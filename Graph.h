//
// Created by omril on 05/07/2022.
//

#ifndef EXERCISE_2_GRAPH_H
#define EXERCISE_2_GRAPH_H

#include "Ex2.h"
#include "Station.h"
#include <vector>
#include <list>
#include <iostream>
#include <cstring>
#include <memory>

template <class V>
class Graph {
private:
    vector<V> graph;
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

    int getVertexIndex(V v);
    Graph<V> getReverse();

    void outBound(V src);               // [2]  V
    void inBound(V dest);               // [3]  V
    int uniExpress(V src, V dest);      // [4]
    int multiExpress(V src, V dest);    // [5]
    void print();                       // [6]  V

};

#endif //EXERCISE_2_GRAPH_H

//
// Created by Omri Leizerovitch on 05/07/2022.
//

#ifndef EXERCISE_2_GRAPH_H
#define EXERCISE_2_GRAPH_H

#include "Ex2.h"
#include "Station.h"
#include <map>
#include <utility>
#include <vector>
#include <list>
#include <iostream>
#include <cstring>
#include <memory>

class Graph {
private:
    vector<Station> graph;   // maybe map<string,V> graph
//    vector<E> edges;
    string graphType;
    const int stop_t;
    Transit_time tt;

public:
    Graph(Transit_time t, string gt, int st) : tt(t), graphType(std::move(gt)), stop_t(st) {}

    void addVertex(string v);
    void addEdge(const string& src, const string& dest, double w);
    bool containVertex(const string& v) const;
    bool containEdge(const string& src, const string& dest, double w) const;


    int getVertexIndex(const string& v) const;
    Graph& getReverse();

    void outBound(string src);                  // [2]  V
    void inBound(string dest);                  // [3]  V
    void uniExpress(string src, string dest);   // [4]
    void multiExpress(string src, string dest); // [5]
    void print();                               // [6]  V

};

#endif //EXERCISE_2_GRAPH_H

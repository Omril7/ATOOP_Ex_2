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
    vector<Station> graph;  // vector of Stations(in stations we have vector of edges)
    string graphType;       // bus\tram\sprinter\rail
    const int waiting_t;    // per vehicle
    Transit_time tt;        // information of all kind of stations

public:
    Graph(Transit_time t, string gt, int st) : tt(t), graphType(std::move(gt)), waiting_t(st) {}

    void addVertex(string v);
    void addEdge(const string& src, const string& dest, double w);
    bool containVertex(const string& v) const;
    bool containEdge(const string& src, const string& dest, double w) const;

    vector<Station> getGraph() const {return graph;}
    string getGraphT() const {return graphType;}
    int getWT() const {return waiting_t;}

    int getVertexIndex(const string& v) const;
    Graph& getReverse();

    void outBound(string src);                                      // [2]  V
    void inBound(string dest);                                      // [3]  V
    void uniExpress(string src, string dest);                       // [4]
    void multiExpress(string src, string dest);                     // [5]
    friend ostream& operator<<(ostream& os, const Graph& graph);    // [6] V
};
inline ostream& operator<<(ostream& os, const Graph& graph) {
    os << graph.getGraphT() << " : " << endl;
    for(int i=0; i<static_cast<int>(graph.getGraph().size()); i++) {
        os << '\t' << graph.getGraph()[i].getName() << " -> ";
        for(int j=0; j<static_cast<int>(graph.getGraph()[i].getAdj().size()); j++) {
            os << (graph.getGraph()[i].getAdj())[j].dest << "(" << (graph.getGraph()[i].getAdj())[j].weight << ") ";
        }
        os << endl;
    }
    return os;
}

#endif //EXERCISE_2_GRAPH_H

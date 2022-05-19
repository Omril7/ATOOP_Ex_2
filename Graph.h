//
// Created by Omri Leizerovitch on 05/07/2022.
//

#ifndef EXERCISE_2_GRAPH_H
#define EXERCISE_2_GRAPH_H

#include "Station.h"
struct Transit_time;

class Graph {
private:
    vector<Station> graph;  // vector of Stations(in stations we have vector of edges)
    Transit_time tt;        // information of all kind of stations
    string graphType;       // bus\tram\sprinter\rail
    const int waiting_t;    // per vehicle

public:
    Graph() : graphType("Q"), waiting_t(0) {}
    Graph(Transit_time t, string gt, int st) : graphType(std::move(gt)), waiting_t(st) {
        tt.centraal = t.centraal;
        tt.intercity = t.intercity;
        tt.stad = t.stad;
    }

    void addVertex(string v);
    void addEdge(const string& src, const string& dest, double w);
    bool containVertex(const string& v) const;
    bool containEdge(const string& src, const string& dest) const;

    vector<Station> getGraph() const {return graph;}
    string getGraphT() const {return graphType;}

    int getVertexIndex(const string& v) const;
    Graph& getReverse();

    bool load(string filename);                                     // [1]  V
    void outBound(string src);                                      // [2]  V
    void inBound(string dest);                                      // [3]  V
    void uniExpress(string src, string dest);                       // [4]  V
    void multiExpress(string src, string dest);                     // [5]
    friend ostream& operator<<(ostream& os, const Graph& graph);    // [6]  V
};
inline ostream& operator<<(ostream& os, const Graph& graph) {
    os << graph.getGraphT() << " : " << endl;
    for(int i=0; i<static_cast<int>(graph.getGraph().size()); i++) {
        os << '\t' << graph.getGraph()[i].getName() << "\t-> ";
        for(int j=0; j<static_cast<int>(graph.getGraph()[i].getAdj().size()); j++) {
            os << (graph.getGraph()[i].getAdj())[j].dest << "(" << (graph.getGraph()[i].getAdj())[j].weight << ")\t";
        }
        os << endl;
    }
    return os;
}

#endif //EXERCISE_2_GRAPH_H

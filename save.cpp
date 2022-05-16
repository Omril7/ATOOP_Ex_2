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

//
// Station.h
//

#ifndef EXERCISE_2_STATION_H
#define EXERCISE_2_STATION_H

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include "Ex2.h"

using namespace std;

class Station;

struct edge {
    Station* dest;
    double weight;
};

class Station {
private:
    string name;
    int transit_t{};
    bool visited = false;
    vector<edge> adjList;

public:
    Station() = default;
    Station(string n, int t) : name(std::move(n)), transit_t(t) {}

    string getName() const {return name;}
    int getTT() const {return transit_t;}
    bool isVisited() const {return visited;}
    vector<edge> getAdj() const {return adjList;}

    void changeVisit(bool a) {visited = a;}

    bool containEdge(const string& dest, double w) const;
    void addEdge(string dest, double w, Transit_time tt);
};


class Intercity : public Station {
public:
    Intercity(string name, int t=15) : Station(name, t) {cout << "Intercity c'tor\n";}
};
class Centraal : public Station {
public:
    Centraal(string name, int t=10) : Station(name, t) {cout << "Centraal c'tor\n";}
};
class Stad : public Station {
public:
    Stad(string name, int t=5) : Station(name, t) {cout << "Stad c'tor\n";}
};

#endif //EXERCISE_2_STATION_H

//
// Station .cpp
//

#include "Station.h"

bool Station::containEdge(const string& dest, double w) const {
    for(auto i : adjList) {
        if(i.dest->getName() == dest && i.weight == w) {
            return true;
        }
    }
    return false;
}
void Station::addEdge(string dest, double w, Transit_time tt) {
    if(!containEdge(dest, w)) {
        edge e;
        if(dest[0] == 'I' && dest[1] == 'C') { // intercity
            e.dest = new Intercity(dest, tt.intercity);
        }
        if(dest[0] == 'C' && dest[1] == 'S') { // centraal
            e.dest = new Centraal(dest, tt.centraal);
        }
        else { // stad
            e.dest = new Stad(dest, tt.stad);
        }
        e.weight = w;
        adjList.push_back(e);
    }
}


typedef pair<int, int> iPair;
void Graph::shortestPath(int src) {

    priority_queue<iPair, vector <iPair> , greater<iPair> > pq;

    // Create a vector for distances and initialize all
    // distances as infinite (INF)
    vector<int> dist(V, INF);

    // Insert source itself in priority queue and initialize
    // its distance as 0.
    pq.push(make_pair(0, src));
    dist[src] = 0;

    /* Looping till priority queue becomes empty (or all
      distances are not finalized) */
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum distance
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted distance (distance must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();

        // 'i' is used to get all adjacent vertices of a vertex
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = (*i).first;
            int weight = (*i).second;

            //  If there is shorted path to v through u.
            if (dist[v] > dist[u] + weight)
            {
                // Updating distance of v
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    // Print shortest distances stored in dist[]
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}
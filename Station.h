//
// Created by Omri Leizerovitch on 05/07/2022.
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
    string dest;
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

    bool containEdge(const string& dest) const;
    void addEdge(string dest, double w, Transit_time tt);
};


class Intercity : public Station {
public:
    Intercity(string name, int t=15) : Station(name, t) {}
};
class Centraal : public Station {
public:
    Centraal(string name, int t=10) : Station(name, t) {}
};
class Stad : public Station {
public:
    Stad(string name, int t=5) : Station(name, t) {}
};

#endif //EXERCISE_2_STATION_H
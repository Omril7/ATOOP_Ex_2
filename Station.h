//
// Created by Omri Leizerovitch on 05/07/2022.
//

#ifndef EXERCISE_2_STATION_H
#define EXERCISE_2_STATION_H

#include <string>
#include <utility>
#include <vector>
#include <memory>

using namespace std;

class Station;

struct edge {
    char type;
    int weight;
//    unique_ptr<Station> dest;
};

class Station {
private:
    string name;
    int transit_t{};
    bool visited = false;
    vector<edge> neighbors;

public:
    Station() = default;
    Station(string n, int t) : name(std::move(n)), transit_t(t) {}
    void addNeighbor(char type, int w, unique_ptr<Station> dest) {
        edge e;
        e.type = type;
        e.weight = w;
//        e.dest = std::move(dest);
        neighbors.push_back(e);
    }

    string getName() const {return name;}
    void changeVisit(bool a) {visited = a;}
    bool isVisited() const {return visited;}
    std::vector<edge> getAdj() const {return neighbors;}
    int numOfAdj() const {return neighbors.size();}
    void resetAdj() {neighbors.resize(0);}
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
//
// Created by Omri Leizerovitch on 05/07/2022.
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
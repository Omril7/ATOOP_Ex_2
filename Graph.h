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


class Graph {
private:
    vector<Station> graph;
    Waiting_time wt;
    Transit_time tt;

public:
    Graph(Waiting_time w, Transit_time t) : wt(w), tt(t) {}
    void printWT() const {
        std::cout << "bus wt: " << wt.bus << std::endl;
        std::cout << "tram wt: " << wt.tram << std::endl;
        std::cout << "sprinter wt: " << wt.sprinter << std::endl;
        std::cout << "rail wt: " << wt.rail << std::endl;
    }
    void printTT() const {
        std::cout << "intercity tt: " << tt.intercity << std::endl;
        std::cout << "centraal tt: " << tt.centraal << std::endl;
        std::cout << "stad tt: " << tt.stad << std::endl;
    }
    void addStation(const Station& station) {
        for(auto & i : graph) {
            if(i.getName() == station.getName()) {
                return;
            }
        }
        graph.push_back(station);
    }
    void addEdge(const Station& a, const Station& b, int w, char t) {
        addStation(a);
        addStation(b);
        for(auto & i : graph) {
            if(i.getName() == a.getName()){
                i.addNeighbor(t, w, b);
                return;
            }
        }
    }
    int getPlace(const Station& a) const {
        for(int i=0; i<graph.size(); i++) {
            if(graph[i].getName() == a.getName()) {
                return i;
            }
        }
    }
    void outbound(Station& source, char type) {
        if(type == 'b') {
            cout << "bus: ";
        }
        if(type == 't') {
            cout << "tram: ";
        }
        if(type == 's') {
            cout << "sprinter: ";
        }
        if(type == 'r') {
            cout << "rail: ";
        }
        int count = 0;
        list<Station> queue;
        graph[getPlace(source)].changeVisit(true);
        queue.push_back(source);
        while(!queue.empty()) {
            source = queue.front();
            queue.pop_front();
            for(auto adj : graph[getPlace(source)].getAdj()) {
                if(!adj.second.second.isVisited() && adj.first == type) {
                    count++;
                    adj.second.second.changeVisit(true);
                    cout << adj.second.second.getName() << '\t';
                    queue.push_back(adj.second.second);
                }
            }
        }
        if(count == 0) {
            cout << "no outbound travel" << endl;
        }
        for(int i=0; i<graph.size(); i++) {
            graph[i].changeVisit(false);
        }
    } // BFS
    void inbound(Station& destination, char type) {
        vector<Station> rev;
        for(int i=0; i<graph.size(); i++) {
            rev.push_back(graph[i]);
            rev[i].resetAdj();
        }
        for(int i=0; i<graph.size(); i++) {
            for(int j=0; j<graph[i].getAdj().size(); j++) {
                char t = graph[i].getAdj()[j].first;
                int w = graph[i].getAdj()[j].second.first;
                rev[getPlace(graph[i].getAdj()[j].second.second)].addNeighbor(t, w, graph[i]);
            }
        }

        if(type == 'b') {
            cout << "bus: ";
        }
        if(type == 't') {
            cout << "tram: ";
        }
        if(type == 's') {
            cout << "sprinter: ";
        }
        if(type == 'r') {
            cout << "rail: ";
        }
        int count = 0;
        list<Station> queue;
        rev[getPlace(destination)].changeVisit(true);
        queue.push_back(destination);
        while(!queue.empty()) {
            destination = queue.front();
            queue.pop_front();
            for(auto adj : rev[getPlace(destination)].getAdj()) {
                if(!adj.second.second.isVisited() && adj.first == type) {
                    count++;
                    adj.second.second.changeVisit(true);
                    cout << adj.second.second.getName() << '\t';
                    queue.push_back(adj.second.second);
                }
            }
        }
        if(count == 0) {
            cout << "no outbound travel" << endl;
        }
    } // rev BFS

    //--------------------------------------------------------------------------------------------//

    void uniExpress(Station& source, Station& destination, char type) {
        int dist;
        if(type == 'b') {
            cout << "bus: ";
        }
        if(type == 't') {
            cout << "tram: ";
        }
        if(type == 's') {
            cout << "sprinter: ";
        }
        if(type == 'r') {
            cout << "rail: ";
        }
        int count = 0;

        if(count == 0) { //// check!
            cout << "route unavailable" << endl;
        }
    } // shortest path (Dijkstra)
    void multiExpress(Station& source, Station& destination) {
        int dist;
        int count = 0;

        if(count == 0) { //// check!
            cout << "route unavailable" << endl;
        }
    } // shortest path (Dijkstra)
};

#endif //EXERCISE_2_GRAPH_H

//
// Created by Omri Leizerovitch on 05/07/2022.
//

#ifndef EXERCISE_2_EX2_H
#define EXERCISE_2_EX2_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

struct Waiting_time {
    int bus = 1;
    int tram = 2;
    int sprinter = 3;
    int rail = 5;
};
struct Transit_time {
    int intercity = 15;
    int centraal = 10;
    int stad = 5;
    Transit_time() : intercity(15), centraal(10), stad(5) {}
};

class Ex2 {
private:
    Waiting_time wt;
    Transit_time tt;
public:
    Ex2(char* config);
    Waiting_time getWT() const {return wt;}
    Transit_time getTT() const {return tt;}
};


#endif //EXERCISE_2_EX2_H

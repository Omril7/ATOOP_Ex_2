//
// Created by Omri Leizerovitch on 05/07/2022.
//

#include "Ex2.h"

Ex2::Ex2(char *config) {
    if(config != nullptr){
        ifstream cnfg(config);
        if (!cnfg) {
            cerr << "error: invalid input." << endl;
            exit(-1);
        }
        string buffer, word;
        stringstream ss;
        int num;
        int count;
        while(getline(cnfg, buffer, '\n')) {
            count = 0;
            char type;
            ss.clear();
            ss.str(buffer);
            while(ss >> word && count < 2) {
                if(word == "bus") {
                    type = 'b';
                }
                if(word == "tram") {
                    type = 't';
                }
                if(word == "sprinter") {
                    type = 's';
                }
                if(word == "rail") {
                    type = 'r';
                }
                if(word == "intercity") {
                    type = 'i';
                }
                if(word == "centraal") {
                    type = 'c';
                }
                if(word == "stad") {
                    type = 'd';
                }
                else {
                    std::istringstream(word) >> num;
                }
                count++;
            }
            if(type == 'b') {
                wt.bus = num;
            }
            if(type == 't') {
                wt.tram = num;
            }
            if(type == 's') {
                wt.sprinter = num;
            }
            if(type == 'r') {
                wt.rail = num;
            }
            if(type == 'i') {
                tt.intercity = num;
            }
            if(type == 'c') {
                tt.centraal = num;
            }
            if(type == 'd') {
                tt.stad = num;
            }
        }
    }
}
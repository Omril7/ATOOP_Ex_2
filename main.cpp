#include <iostream>
#include "Graph.h"
#include "Ex2.h"
#include <cstring>
#include <array>

int main(int argc, char** argv) {
    if(argc < 3) {
        cerr << "Not enough information" << endl;
        exit(-1);
    }
    char* config = nullptr;
    string output = "output.dat";
    std::vector<char*> input_files;
    int i=2;
    while(strcmp(argv[i],"-c") != 0 && strcmp(argv[i],"-o") != 0 && i<argc) {
        input_files.push_back(argv[i]);
        i++;
    }
    while(i<argc) {
        if(strcmp(argv[i],"-c") == 0) {
            config = argv[i+1];
            i += 2;
            continue;
        }
        if(strcmp(argv[i], "-o") == 0) {
            output = argv[i+1];
            i += 2;
            continue;
        }
    }

    Ex2 *ex2 = new Ex2(config);
    Graph<Station> busGraph(ex2->getTT(), "bus", ex2->getWT().bus);
    Graph<Station> tramGraph(ex2->getTT(), "tram", ex2->getWT().tram);
    Graph<Station> sprinterGraph(ex2->getTT(), "sprinter", ex2->getWT().sprinter);
    Graph<Station> railGraph(ex2->getTT(), "rail", ex2->getWT().rail);

//    busGraph.printTT();
//    tramGraph.printTT();
//    sprinterGraph.printTT();
//    railGraph.printTT();


    string line, command, word;
    string params[2];
    int count;
    while(line != "EXIT") {
        count = 0;
        getline(cin, line);
        istringstream iss(line);
        while(iss >> word) {
            if(count == 0) {
                command = word;
            }
            else {
                params[count-1] = word;
            }
            count++;
        }
        if(command == "load") {
            cout << "now loaded file: " << params[0] << endl;
//            if(loaded) {
//                cout << "Update was successful." << endl;
//            }
//            else {
//                cerr << "ERROR opening the specified file." << endl;
//            }
        }
        if(command == "outbound") {
//            busGraph.outBound(params[0]);
//            tramGraph.outBound(params[0]);
//            sprinterGraph.outBound(params[0]);
//            railGraph.outBound(params[0]);
            cout << "now outbound: " << params[0] << endl;
        }
        if(command == "inbound") {
//            busGraph.inBound(params[0]);
//            tramGraph.inBound(params[0]);
//            sprinterGraph.inBound(params[0]);
//            railGraph.inBound(params[0]);
            cout << "now inbound: " << params[0] << endl;
        }
        if(command == "uniExpress") {
//            busGraph.uniExpress(params[0], params[1]);
//            tramGraph.uniExpress(params[0], params[1]);
//            sprinterGraph.uniExpress(params[0], params[1]);
//            railGraph.uniExpress(params[0], params[1]);
            cout << "now uniExpress: " << params[0] << " " << params[1] << endl;
        }
        if(command == "multiExpress") {
            cout << "now multiExpress: " << params[0] << " " << params[1] << endl;
        }
        if(command == "print") {
//            busGraph.print();
//            tramGraph.print();
//            sprinterGraph.print();
//            railGraph.print();
            cout << "now printing to " << output << " the graph" << endl;
        }
        iss.clear();
    }
    return 0;
}

#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
#include <iostream>
#include "Driver.h"

using namespace std;

int main(int argc, char **argv) {
    if(argc <= 1){
        Catch::Session().run();
        return 0;
    }
    ifstream data(argv[1]);     //data file
    ifstream input(argv[2]);    //input cities file
    ofstream output(argv[3]);   //output file

    JPLinkedList<JPLinkedList<Cities> *> JPAdjList; //Adjacency List
    JPVector<JPVector<JPString>> outputList;        //Output Vector
    JPVector<Cities> requestedRoutes;               //Input Vector
    JPStack jpStack;                                //Stack

    parseRequested(requestedRoutes, input); //Parse the input file and populate the requested routes vector

    parseInputFile(JPAdjList, data);        //parse the data file and populate the Adjacency List

    getOutput(JPAdjList, requestedRoutes, outputList, output, jpStack, data); //call the output method with all of the variables

    //close all files
    data.close();
    input.close();
    output.close();
    return 0;
}


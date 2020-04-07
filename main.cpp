#include <iostream>
#include "Driver.h"

using namespace std;






int main(int argc, char **argv) {

    ifstream data(argv[1]);
    ifstream input(argv[2]);
    ofstream output(argv[3]);

    JPLinkedList<JPLinkedList<Cities> *> JPAdjList;
    JPLinkedList<JPLinkedList<JPString>*> outputList;
    JPLinkedList<Cities> requestedRoutes;
    JPStack jpStack;

    parseRequested(requestedRoutes, input);

    parseInputFile(JPAdjList, data);

    JPIterator<JPLinkedList<Cities>*>* jpIterator = JPAdjList.getHeadIterator();
    while(jpIterator->nextNode() != NULL) {
        JPIterator<Cities>* jpIterator1 = jpIterator->getNode()->data->getHeadIterator();
        while(jpIterator1->nextNode() != NULL) {
            cout << jpIterator1->getNode()->data << "-->";
        }
        cout << "|" << endl;
        delete jpIterator1;
    }
    cout << "End of Listings \n" << endl;

    getOutput(JPAdjList, requestedRoutes, outputList, output, jpStack);

    JPIterator<JPLinkedList<JPString>*>* jpIterator2 = outputList.getHeadIterator();
    while(jpIterator2->nextNode() != NULL) {
        JPIterator<JPString>* jpIterator1 = jpIterator2->getNode()->data->getHeadIterator();
        jpIterator1->nextNode();
        while(jpIterator1->nextNode() != NULL) {
            cout << jpIterator1->getNode()->data << "<--";
        }
        cout << "|" << endl;
        delete jpIterator1;
    }
    cout << "End of Output \n" << endl;

    JPIterator<Cities>* jpIterator3 = requestedRoutes.getHeadIterator();
    while(jpIterator3->nextNode() != nullptr){
        cout << jpIterator3->getNode()->data  << " :: " << jpIterator3->getNode()->data.getCost() << " :: " << jpIterator3->getNode()->data.getTime() << endl;
    }

    delete jpIterator3;
    delete jpIterator;
    delete jpIterator2;
    return 0;
}

#include <iostream>
#include "Driver.h"

using namespace std;






int main(int argc, char **argv) {

    ifstream data(argv[1]);
    ifstream input(argv[2]);
    ofstream output(argv[3]);

    JPLinkedList<JPLinkedList<Cities> *> JPAdjList;
    JPStack jpStack;

    JPString origin("Houston");
    JPString destination("Chicago");
    int cost;
    int time;
    Cities requested(origin, destination, cost, time);
    Cities requested1(destination, origin, cost, time);


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

    iterativeBacktrack(JPAdjList, jpStack, requested);


    delete jpIterator;
    return 0;
}

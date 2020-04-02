//
// Created by jacks on 3/27/2020.
//

#include "Driver.h"
#include <sstream>

void mainDriver() {
    int i = 0;
    int j = 1;
    int k = 2;
    int l = 3;

    JPLinkedList<JPLinkedList<int> *> jpAdjList;
    auto *jpLinkedList4 = new JPLinkedList<int>;
    auto *jpLinkedList5 = new JPLinkedList<int>;

    jpLinkedList4->append(i);
    jpLinkedList4->append(k);
    jpLinkedList4->append(j);
    jpLinkedList4->append(l);
    jpLinkedList4->append(l);
    jpLinkedList4->append(j);

    jpLinkedList5->append(l);
    jpLinkedList5->append(j);
    jpLinkedList5->append(j);
    jpLinkedList5->append(k);
    jpLinkedList5->append(l);
    jpLinkedList5->append(j);
    jpLinkedList5->append(j);
    jpLinkedList5->append(k);

    jpAdjList.append(jpLinkedList4);
    jpAdjList.append(jpLinkedList5);
    jpAdjList.append(jpLinkedList4);
    jpAdjList.append(jpLinkedList5);
    jpAdjList.append(jpLinkedList4);
    jpAdjList.append(jpLinkedList4);
    jpAdjList.append(jpLinkedList5);
    jpAdjList.append(jpLinkedList5);


    jpAdjList.moveToHead();
    for (int m = 0; m < jpAdjList.length(); m++) {
        jpAdjList.getValue()->print();
        jpAdjList.moveToRight();
    }


    delete jpLinkedList4;
    delete jpLinkedList5;

}

void parseInputFile(JPLinkedList<JPLinkedList<JPString> *> &JPAdjList, ifstream &inFile) {
    char *line = new char[80];
    char *origin = new char[20];
    char *dest = new char[20];
    char *cost = new char[20];
    char *minutes = new char[20];

    inFile.getline(line, 80);
    int length = atoi(line);
    for (int i = 0; i < length; i++) {
        inFile.getline(line, 80);
        stringstream ss(line);
        while (!ss.eof()) {
            ss.getline(origin, 20, '|');
            ss.getline(dest, 20, '|');
            ss.getline(cost, 20, '|');
            ss.getline(minutes, 20);

            JPString JPOrigin(origin);
            JPString JPDest(dest);

            if (JPAdjList.length() == 0) {
                emptyList(JPAdjList, JPOrigin, JPDest);
            } else {
                JPAdjList.moveToHead();
                bool isOrigin;
                searchInList(JPAdjList, JPOrigin, JPDest, isOrigin = false);
                JPAdjList.moveToHead();
                bool isDest;
                searchInList(JPAdjList, JPDest, JPOrigin, isDest = false);
                JPAdjList.moveToHead();
                JPAdjList.getValue()->moveToHead();
                addNewList(JPAdjList, JPOrigin, JPDest, isOrigin);
                addNewList(JPAdjList, JPDest, JPOrigin, isDest);
                JPAdjList.moveToRight();
            }
        }
    }

    delete[] line;
    delete[] origin;
    delete[] dest;
    delete[] cost;
    delete[] minutes;
}

void emptyList(JPLinkedList<JPLinkedList<JPString> *> & JPAdjList, JPString & JPOrigin, JPString & JPDest) {
    auto *jpLinkedList = new JPLinkedList<JPString>;
    jpLinkedList->moveToHead();
    jpLinkedList->insert(JPOrigin);
    jpLinkedList->append(JPDest);
    JPAdjList.moveToHead();
    JPAdjList.insert(jpLinkedList);
    auto *jpLinkedList1 = new JPLinkedList<JPString>;
    jpLinkedList1->moveToHead();
    jpLinkedList1->insert(JPDest);
    jpLinkedList1->append(JPOrigin);
    JPAdjList.append(jpLinkedList1);
}

void searchInList(JPLinkedList<JPLinkedList<JPString> *> & JPAdjList, JPString & head, JPString & elem, bool & isThere){
    for (int j = 0; j < JPAdjList.length(); j++) {
        isThere = false;
        JPAdjList.getValue()->moveToHead();
        if (JPAdjList.getValue()->getValue() == head) {
            JPAdjList.getValue()->moveToHead();
            JPAdjList.getValue()->append(elem);
            break;
        } else { isThere = true; }
        JPAdjList.moveToRight();
    }
}
void addNewList(JPLinkedList<JPLinkedList<JPString> *> & JPAdjList, JPString & head, JPString & elem, bool & isThere){
    if (isThere) {
        auto *jpLinkedList = new JPLinkedList<JPString>;
        jpLinkedList->moveToHead();
        jpLinkedList->insert(head);
        jpLinkedList->append(elem);
        JPAdjList.moveToHead();
        JPAdjList.insert(jpLinkedList);
    }
}
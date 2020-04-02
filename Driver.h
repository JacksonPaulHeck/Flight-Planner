//
// Created by jacks on 3/27/2020.
//
#include "JPStack.h"
#include "JPLinkedList.h"
#include "JPString.h"

#ifndef S20_PA04_FLIGHTPLANNER_DRIVER_H
#define S20_PA04_FLIGHTPLANNER_DRIVER_H

using namespace std;

void mainDriver();

void parseInputFile(JPLinkedList<JPLinkedList<JPString>*> &, ifstream &);

void emptyList(JPLinkedList<JPLinkedList<JPString> *> &, JPString &, JPString &);

void searchInList(JPLinkedList<JPLinkedList<JPString> *> &, JPString &, JPString &, bool &);

void addNewList(JPLinkedList<JPLinkedList<JPString> *> &, JPString &, JPString &, bool &);



#endif //S20_PA04_FLIGHTPLANNER_DRIVER_H

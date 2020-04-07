//
// Created by jacks on 3/27/2020.
//

#ifndef S20_PA04_FLIGHTPLANNER_DRIVER_H
#define S20_PA04_FLIGHTPLANNER_DRIVER_H

#include "JPStack.h"
#include "JPLinkedList.h"
#include "JPIterator.h"
#include "Cities.h"

using namespace std;

void parseInputFile(JPLinkedList<JPLinkedList<Cities>*> &, ifstream &);

void parseRequested(JPLinkedList<Cities> &, ifstream &);

void getOutput(JPLinkedList<JPLinkedList<Cities> *> &, JPLinkedList<Cities> &, JPLinkedList<JPLinkedList<JPString> *> &, ofstream &, JPStack & jpStack);

void emptyList(JPLinkedList<JPLinkedList<Cities> *> &, Cities &, Cities &);

void searchInList(JPLinkedList<JPLinkedList<Cities> *> &, Cities &, bool &);

void addNewList(JPLinkedList<JPLinkedList<Cities> *> &, Cities &, bool &);

void iterativeBacktrack(JPLinkedList<JPLinkedList<Cities> *> &, JPStack &, const Cities &, JPLinkedList<JPLinkedList<JPString>*> &);



#endif //S20_PA04_FLIGHTPLANNER_DRIVER_H

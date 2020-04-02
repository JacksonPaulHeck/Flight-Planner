#include <iostream>
#include "Driver.h"
using namespace std;

int main(int argc, char** argv){

    ifstream data(argv[1]);
    ifstream input(argv[2]);
    ofstream output(argv[3]);

    JPLinkedList<JPLinkedList<JPString>*> JPAdjList;

    //mainDriver();

    parseInputFile(JPAdjList, data);

    JPAdjList.moveToHead();
    for(int i = 0; i < JPAdjList.length(); i++){
        JPAdjList.getValue()->print();
        JPAdjList.moveToRight();
    }

    JPStack<JPString> jpStack;

    JPString jpString("JPString");
    JPString jpString1("JPString1");
    JPString jpString2("JPString2");

    jpStack.push(jpString);
    jpStack.push(jpString1);
    jpStack.pop();
    jpStack.push(jpString2);
    jpStack.push(jpString1);


    cout << jpStack.pop() << endl;
    cout << jpStack.pop() << endl;
    cout << jpStack.pop() << endl;


    return 0;
}

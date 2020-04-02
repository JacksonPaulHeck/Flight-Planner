//
// Created by jacks on 3/26/2020.
//
#include "JPNode.h"

#ifndef S20_PA04_FLIGHTPLANNER_JPLINKEDLIST_H
#define S20_PA04_FLIGHTPLANNER_JPLINKEDLIST_H

template<typename T>
class JPLinkedList {
private:
    JPNode<T> *head;
    JPNode<T> *tail;
    JPNode<T> *curr;
    int count;

    void init() {
        curr = tail = head = new JPNode<T>;
        count = 0;
    }

    void removeAll() {
        while (head != NULL) {
            JPNode<T> *curr = head;
            head = head->next;
            delete curr;
        }
    }

public:
    JPLinkedList() { init(); };

    ~JPLinkedList() { removeAll(); }

    void print() const;

    void clear() {
        removeAll();
        init();
    }

    void insert(const T &it) {
        curr->next = new JPNode<T>(it, curr->previous, curr->next);
        if (tail == curr) {
            tail = curr->next;
        }
        count++;
    }

    void append(const T &it) {
        tail = tail->next = new JPNode<T>(it, NULL, NULL);
        count++;
    }

    T remove() {
        T it = curr->next->data;
        JPNode<T> *linkTemp = curr->next;
        if (tail == curr->next) {
            tail = curr;
        }
        curr->next = curr->next->next;
        delete linkTemp;
        count--;
        return it;
    }

    void moveToHead() {
        curr = head;
    }

    void moveToTail() {
        curr = tail;
    }

    void moveToLeft() {
        if (curr == head) {
            return;
        }
        JPNode<T> * temp = head;
        while(temp->next != curr){
            temp = temp->next;
        }
        curr = temp;
    }
    void moveToRight() {
        if (curr != tail) {
            curr = curr->next;
        }
    }
    int length() const{
        return count;
    }
    void moveToPosition(int pos){
        curr = head;
        for(int i = 0; i < pos; i++){
            curr = curr->next;
        }
    }
    const T& getValue()const{
        return curr->next->data;
    }
};

template<typename T>
void JPLinkedList<T>::print() const {
    JPNode<T> * temp = head->next;
    while(temp!=NULL){
        std::cout << temp->data << "-->";
        temp = temp->next;
    }
    std::cout << "|" << std::endl;
}

#endif //S20_PA04_FLIGHTPLANNER_JPLINKEDLIST_H

//
// Created by jacks on 3/26/2020.
//
#include "JPNode.h"
#include "JPIterator.h"

#ifndef S20_PA04_FLIGHTPLANNER_JPLINKEDLIST_H
#define S20_PA04_FLIGHTPLANNER_JPLINKEDLIST_H

template<typename T>
class JPLinkedList {
    friend class JPStack;

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

    JPLinkedList(JPLinkedList<T> & listToCopy){
        init();
        if(!listToCopy.isEmpty()) {
            JPNode<T>* curr = listToCopy.head;
            while(curr != NULL){
                append(curr->data);
                curr = curr->next;
            }
        }
    }

    JPLinkedList<T> & operator=(JPLinkedList<T> const & listToCopy){
        init();
        if(!listToCopy.isEmpty()) {
            JPNode<T>* copyCurr = listToCopy.head;
            while(copyCurr != NULL){
                append(copyCurr->data);
                copyCurr = copyCurr->next;
            }
        }
    }

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

    void moveCurrToHead() {
        curr = head;
    }

    bool isEmpty(){
        return head->next == nullptr;
    }

    void moveCurrToTail() {
        curr = tail;
    }

    void moveCurrToLeft() {
        if (curr != head) {
            curr = curr->previous;
        }
    }

    void moveCurrToRight() {
        if (curr != tail) {
            curr = curr->next;
        }
    }

    int length(){
        return count;
    }

    void moveToPosition(int pos){
        curr = head;
        for(int i = 0; i < pos; i++){
            curr = curr->next;
        }
    }


    JPIterator<T> *getHeadIterator()const{
        return new JPIterator<T>(head);
    }

    JPIterator<T> *getCurrIterator()const{
        return new JPIterator<T>(curr);
    }

    JPIterator<T> *getTailIterator()const{
        return new JPIterator<T>(tail);
    }

    const T& getCurrValue()const{
        return curr->next->data;
    }

    JPNode<T> *& getCurrNextNode(){
        return curr->next;
    }
    JPNode<T> *& getCurrNode(){
        return curr;
    }


    bool contains(const T& requested){
        JPNode<T> tp = head->next;
        while(tp != NULL){
            if(tp->data == requested){
                return true;
            }
            tp = tp -> next;
        }
        return false;
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

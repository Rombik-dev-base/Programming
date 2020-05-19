//
// Created by 1285166 on 08.04.2020.
//

#ifndef INC_5THPROGRAM_MYQUEUE_H
#define INC_5THPROGRAM_MYQUEUE_H

#include <iostream>

using namespace std;

class MyQueueException : public exception{};

class EmptyException : public MyQueueException{
public:
    const char* what() const throw() override{
        return "Empty Queue!";
    }
};

class OversizedException : public  MyQueueException{
public:
    const char* what() const throw() override {
        return "Oversized!";
    }
};

template<int N, typename T>
class MyQueue {
public:
    MyQueue(){
        maxsize_ = N;
        size_ = 0;
        Q -> First = nullptr;
        Q -> Last = nullptr;
    };

    ~MyQueue(){
        while(Q->First != NULL){
            Node *next = Q->First->next;
            delete Q->First;
            Q->First = next;
            delete next;
        }
    }
    void push(T elem){
        if(size_ == maxsize_) {
            throw OversizedException();
        }
        if(size_ == 0){
            inpfirstel(elem);
            return;
        }
        if(size_ < maxsize_) {
            Node *node = new Node;
            Q->Last->next = node;
            Q->Last = node;
            Q->Last->storage = elem;
            Q->Last->next = nullptr;
            size_ += 1;
            cout << size_ << '\n';
        }
    }
    void inpfirstel(T elem) {
        size_ = 1;
        Node *node = new Node;
        Q->First = node;
        Q->First->next = nullptr;
        Q->Last = node;
        Q->Last->storage = elem;
    }
    void pops(){
        if(Q->First == nullptr)
            throw EmptyException();
        Q->First = Q->First->next;
    }

    bool operator <(T elem){
        retrun Q.
    }

    void size();
private:
    struct Node{
        Node *next;
        T storage;
    };
    struct Queue{
        Node *First;
        Node *Last;
    };
    int maxsize_;
    int size_ ;
    Queue *Q = new Queue;
};

#endif //INC_5THPROGRAM_MYQUEUE_H

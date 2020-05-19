//
// Created by 1285166 on 21.04.2020.
//

#ifndef LAB7FUNNY_CONTAINER_H
#define LAB7FUNNY_CONTAINER_H

#include <iostream>
#include "exceptions.h"
#include <iterator>
using namespace std;

class myexception : public exception, public random_access_iterator_tag{
public:
    myexception(char *omg){
        excepinfo = omg;
    }
    const char* what() const throw() override{
        return excepinfo;
    }
    char *excepinfo;
};


template<typename T>
class container : public random_access_iterator_tag  {
public:
    struct element{
        element *next;
        element *prev;
        T cur;
        bool isitend;
        bool previsplus = false;
    };
    container(int capacity = 1){
        capacity_ = capacity;
        if(capacity > 0) {
            end_ = new element;
            begin_ = nullptr;
        }
        // else throw BadSizedExcep;
    }


    ~container(){
        while(size_ > 0){
            element *elem = begin_->next;
            delete begin_;
            begin_ = elem;
            size_ -= 1;
        }
    }


    element* begin(){
        if(size_ == 0){}
        //   throw EmptyException;
        return begin_;
    }
    element* end(){
        if(size_ != 0){}
        return end_;
        // else throw EmptyException;
    }


    void push_begin(T object){
        if(begin_ == nullptr){
            element *elem = new element;
            elem -> cur = object;
            elem -> next = end_;
            elem -> prev = end_;
            elem -> isitend = false;
            begin_ = elem;
            end_ -> next = begin_;
            end_ -> prev = elem;
            end_ -> isitend = true;
            size_ += 1;
            return;
        }
        else if(size_ < capacity_) {
            element *elem = new element;
            elem -> cur = object;
            elem -> next = begin_;
            elem -> prev = end_;
            elem -> isitend = false;
            begin_ -> prev = elem;
            begin_ = elem;
            end_ -> next = begin_;
            size_ += 1;
        }
        else if(size_ == capacity_){
            begin_ -> cur = object;
        }
    }


    void push_end(T object){
        if(begin_ == nullptr){
            element *elem = new element;
            elem -> cur = object;
            elem -> next = end_;
            elem -> prev = elem;
            elem -> isitend = false;
            begin_ = elem;
            end_ -> next = elem;
            end_ -> isitend = true;
            end_ -> prev = elem;
            size_ += 1;
            return;
        }
        if(size_ < capacity_){
            element *elem = new element;
            elem -> cur = object;
            elem -> next = end_;
            elem -> prev = end_ -> prev;
            elem -> isitend = false;
            end_ -> prev -> next = elem;
            end_ -> prev = elem;
            begin_ -> prev = end_ -> prev;
            size_ += 1;
        }
        else if(size_ == capacity_){
            end_ -> prev -> cur = object;
        }
    }


    void pop_begin(){
        if(size_ == 1) {
            delete begin_;
            begin_ = nullptr;
            size_ -=1;
            return;
        }
        if(size_ > 1){
            end_ -> next = begin_ -> next;
            begin_ -> next -> prev = end_;
            delete begin_;
            begin_ = end_ -> next;
            size_ -= 1;
            return;
        }
        throw myexception("Buffer is empty");
    }


    void pop_end(){
        if(size_ == 1){
            delete begin_;
            begin_ = nullptr;
            size_ -= 1;
            return;
        }
        if(size_ > 1){
            element *elem = end_ -> prev;
            end_ -> prev -> prev -> next = end_;
            end_ -> prev = end_ -> prev -> prev;
            delete elem;
            size_ -= 1;
            return;
        }
        throw myexception("Buffer is emty");
    }


    void capacity_change(int newsize){
        if(newsize == 0){};
        // throw BadNewSizeException;
        while(newsize < size_){
            pop_end();
        }
        capacity_ = newsize;
    }

    long long size(){
        return size_;
    }

    T operator [](int i){
        // if(i > size_ - 1 || i < 0)
        //   throw BadPositionException;
        element *element_ = begin_;
        for(int j = 0; j < i; j++)
            element_ = element_ -> next;
        return element_ -> cur;
    }
    class myiter : public std::iterator<std::random_access_iterator_tag, T>{
    public:
        using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
        myiter(){
            iterator = nullptr;
        }
        myiter(element *omg){
            iterator = omg;
        }
        void operator ++(){
            iterator = iterator -> next;
            if(iterator -> isitend)
                iterator -> previsplus = true;
        }
        void operator ++(int){
            iterator = iterator->next;
            if(iterator -> isitend)
                iterator -> previsplus = true;
        }
        void operator --(){
            iterator = iterator->prev;
            if(iterator -> isitend)
                iterator -> previsplus = false;
        }
        void operator --(int){
            iterator = iterator->prev;
            if(iterator -> isitend)
                iterator -> previsplus = false;
        }
        T& operator *(){
            if(iterator -> isitend) {
                if (iterator->previsplus)
                    iterator = iterator -> next;
                else
                    iterator = iterator -> prev;
            }
            return iterator->cur;
        }
        inline myiter& operator+=(difference_type it) { iterator += it; return *this;}
        inline myiter& operator-=(difference_type it) { iterator -= it; return *this;}
        bool operator ==(myiter &cur){
            return iterator == cur.iterator;
        }
        bool operator ==(element* omg){
            return omg == iterator;
        }
        void operator =(myiter cur){
            iterator = cur.iterator;
        }
        void operator =(element* omg){
            iterator = omg;
        }
        bool operator !=(element* omg){
            return iterator != omg;
        }
        bool operator !=(myiter heh){
            return iterator != heh.iterator;
        }
        bool operator < (myiter heh){
            return iterator-> cur < heh.iterator -> cur;
        }
        int operator -(myiter heh){
            element *elem = heh.iterator;
            element *elem2 = iterator;
            int z = 0;
            while(elem2 != elem){
                elem--;
                z += 1;
            }
            return z;
        }
        myiter operator +(int num){
            while(num > 0){
                iterator = iterator -> next;
                num--;
            }
            return *this;
        }
        myiter operator -(int num){
            while(num > 0){
                iterator = iterator -> prev;
                num--;
            }
            return iterator;
        }
        myiter(const myiter &other) : iterator(other.iterator) {}
        inline T& operator*() const {return *iterator;}
        inline T* operator->() const {return iterator;}
        inline T& operator[](difference_type i)
        const {return iterator[i];}
        element *iterator;
    };
private:

    element *begin_ ;
    element *end_ ;
    int size_ = 0;
    int capacity_;
};






#endif //LAB7FUNNY_CONTAINER_H

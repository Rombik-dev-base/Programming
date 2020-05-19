#include <iostream>
#include <string>
#include "MyQueue.h"

template<typename T>
T returned(int N,T type){
    T number = type;
    if(N > 0){
    for(int i = 0; i < N; i ++){
        type *= number;
    }
    return type;
    }
    if(N < 0){
        for(int i = N; i < 0; i++){
            type *= number;
            return 1/type;
        }
    }
    return 0;
}

int main() {
    double a;
    cin >> a;
    cout << returned(-2,a);
    MyQueue<3 , int > myq;
    while(true){
        string command;
        cin >> command;
        if(command == "push"){
            try{
                cout << "Input number:";
                int num;
                cin >> num;
                myq.push(num);
            }
            catch(OversizedException& e){
                cerr << e.what();
            }
        }
        if(command == "pops"){
            try{
                myq.pops();
            }
            catch(EmptyException& e){
                cout << "Empty!\n";
            }
        }
        if(command == "end"){
            cout << "Finished\n";
            break;
        }
    }
    return 0;
}

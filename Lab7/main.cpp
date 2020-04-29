#include <iostream>
#include "container.h"
#include <string>


int main() {
    try {
        container<int> mycheck(3);
        mycheck.push_end(5);
        mycheck.push_end(7);
        mycheck.push_end(89);
        mycheck.push_end(91);
        std::cout << mycheck[0] << '\n';
        container<int>::myiter iter = mycheck.begin();
        iter++;
        std::cout << *iter;
        std::cout << "\nCheck 2\n";
        for (int i = 0; i < mycheck.size(); i++) {
            std::cout << mycheck[i] << ' ';
        }
        std::cout << "\nCheck 3\n";
        for (container<int>::myiter iter1 = mycheck.begin(); iter1 != mycheck.end(); iter1++) {
            std::cout << *iter1 << ' ';
        }
        std::cout << "\n Check 4\n";
        mycheck.capacity_change(1);
        iter = mycheck.begin();
        iter++;
        iter++;
        std::cout << *iter;
    }
    catch(exception &a){
        std :: cerr << a.what();
    }
    return 0;
}

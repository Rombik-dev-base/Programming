#include <iostream>
#include <vector>
#include <afxres.h>
#include "functions.h"
#include <set>
#include "MyQueue.h"
#include "fromlab7.h"

using namespace std;

template<typename T>
T mycomp(T b){
    return b < 1;
}




int main() {
    std :: vector<int> check = {5,5,6,4};
    if(any_of(check.begin(), check.end(),[](int i){ return i < 5;}))
        std :: cout << "TRUE\n";
    else
        std :: cout << "FALSE\n";
    if(one_of(check.begin(),check.end(),[](int i){return i > 5;}))
        std :: cout << "TRUE\n";
    else
        std :: cout << "FALSE\n";
    if(find_not(check.begin(),check.end(),5) != 5)
        std :: cout  << find_not(check.begin(),check.end(),5) << '\n';
    else
        std:: cout << "FALSE\n";
    std :: set <double> check2 = {4.555,4.21312,3.213213,6.546456,1.32432432423,8.43543543,0.435345435};
    if(any_of(check2.begin(),check2.end(),mycomp<double>))
        std :: cout << "TRUE\n";
    else
        std :: cout << "FALSE\n";
    if(one_of(check2.begin(),check2.end(),[](double i){ return i > 2; }))
        std :: cout << "TRUE\n";
    else
        std :: cout << "FALSE\n";
    if(find_not(check2.begin(),check2.end(),5) != 5) {
        double n = find_not(check2.begin(), check2.end(), 5);
        std::cout  << n << '\n';
    }
    else
        std :: cout << "FALSE\n";
    container<int> mycheck(3);
    mycheck.push_end(5);
    mycheck.push_end(7);
    mycheck.push_end(89);
    container<int>::myiter iter = mycheck.begin();
    container<int>::myiter iter2 = mycheck.end();
    if(any_of(iter,iter2, [](int i){ return i > 99;} )){
        cout << "TRUE" << '\n';
    }
    else
        cout << "FALSE" << '\n';
    return 0;
}

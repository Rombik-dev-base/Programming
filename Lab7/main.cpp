#include <iostream>
#include <algorithm>
#include "container.h"

using namespace std;

int main() {
    unsigned int capacity;
    cin >> capacity;
    circular_buffer<int> buffer(capacity);
    int cur_size = 0;
    while(cur_size != capacity){
        int num = 0;
        cin >> num;
        buffer.push_back(num);
        cur_size++;
    }
    for(int i = 0; i < cur_size; i++){
        cout << buffer[i] << ' ';
    }
    cout << '\n';
    buffer.print_all();
    buffer.resize(5);
    buffer.print_all();
    sort(buffer.begin(), buffer.end());
    buffer.print_all();
    auto it = find(buffer.begin(),buffer.end(),2);
    cout << *it << ' ';
    for(auto it = buffer.begin(); it != buffer.end(); it++){
        cout << *it << ' ';
    }
}

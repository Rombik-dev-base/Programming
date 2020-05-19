//
// Created by 1285166 on 21.04.2020.
//

#ifndef LAB6_FUNCTIONS_H
#define LAB6_FUNCTIONS_H

template<class Input, class Comp>
bool any_of(Input start, Input end, Comp comp){
    while(start != end){
        if(comp(*start))
            return true;
        start++;
    }
    return false;
}

template<class Input, class Comp>
bool one_of(Input start, Input end, Comp comp){
    int ans = 0;
    while(start != end){
        if(comp(*start))
            ans += 1;
        start++;
    }
    return ans == 1;
}

template <class Input, class Comp>
double find_not(Input start, Input end, Comp comp){
    while(start != end){
        if(comp != *start)
            return *start;
        start++;
    }
    return comp;
}

#endif //LAB6_FUNCTIONS_H

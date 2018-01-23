//
//  main.cpp
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 23/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

#include "./LinearList/arrayList.hpp"

void print(int &e)
{std::cout << e << " ";}

int main(int argc, const char * argv[]) {
    arrayList<int> a;
    for(int i = 0; i < 10; i++)
        a.insert(i, i);
    std::cout << a << std::endl;
    a.insert(3, 55);
    a.erase(0);
    std::cout << a << std::endl;
    std::cout << a.get(0) << std::endl;
    arrayList<int>::iterator it;
    for(it = a.begin(); it != a.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
    std::for_each(a.begin(), a.end(), print);
    std::cout << a.indexOf(55) << std::endl;
    it = a.begin();
    a.insert(it, 33);
    std::cout << a << std::endl;
    it = a.end();
    a.erase(it);
    std::cout << a << std::endl;
}

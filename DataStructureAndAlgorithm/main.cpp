//
//  main.cpp
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 23/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

/*
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
*/

#include "./LinearList/chain.hpp"
#include "./LinearList//extendedChain.hpp"
int main()
{
    chain<int> a;
    for(int i = 0; i < 10; i++)
        a.insert(i, i);
    std::cout << a << std::endl;
    a.erase(3);
    std::cout << a << std::endl;
    std::cout << a.get(0) << std::endl;
    std::cout << a.indexOf(9) << std::endl;
    
    extendedChain<int> b;
    for(int i = 0; i < 10; i++)
        b.insert(i, i);
    b.push_back(110);
    b.push_back(120);
    std::cout << b << std::endl;
    b.erase(11);
    b.push_back(150);
    std::cout << b << std::endl;
    b.insert(12, 222);
    b.push_back(333);
    std::cout << b << std::endl;
    extendedChain<int> c(b);
    std::cout << c << std::endl;
}

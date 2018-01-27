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
/*
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
}*/
/*
#include "./Matrix/Matrix.hpp"
int main()
{
    double s[9] = {1,0,0,0,1,0,0,0,1};
    matrix<double> a(3,3,s);
    std::cout << a << std::endl;
    std::cout << a.transpose() << std::endl;
    std::cout << a + 2 << std::endl;
    std::cout << a - 2 << std::endl;
    std::cout << a * 2 << std::endl;
    std::cout << a / 2 << std::endl;
    double d[9] = {1,3,5,2,4,6,0,0,0};
    matrix<double> b(3,3,d);
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    std::cout << a * b << std::endl;
}
*/

#include "./stack/derivedArrayStack.hpp"
#include "./stack/arrayStack.hpp"
#include "./stack/linkedStack.hpp"
int main()
{
    derivedArrayStack<int> a(10);
    a.push(1);
    a.push(2);
    a.push(3);
    std::cout << a << std::endl;
    std::cout << a.top() << std::endl;
    a.pop();
    std::cout << a << std::endl;
    arrayStack<int> b(10);
    b.push(1);
    b.push(2);
    b.push(3);
    std::cout << b << std::endl;
    std::cout << b.top() << std::endl;
    b.pop();
    std::cout << b << std::endl;
    linkedStack<int> c(10);
    c.push(1);
    c.push(2);
    c.push(3);
    std::cout << c << std::endl;
    std::cout << c.top() << std::endl;
    c.pop();
    std::cout << c << std::endl;
}

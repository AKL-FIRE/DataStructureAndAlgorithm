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
/*
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
*/

//#include "queue/arrayQueue.h"
//
//int main()
//{
//    arrayQueue<char> a(8);
//    a.push('A');
//    a.push('B');
//    a.push('C');
//    a.push('D');
//    char f = a.front();
//    char b = a.back();
//    a.pop();
//    a.push('E');
//    a.push('F');
//    a.push('G');
//    a.push('H');
//    a.push('I');
//    a.push('J');
//    a.push('K');
//    f = a.front();
//    b = a.back();
//    a.pop();
//}

//#include "graph/linkedWDigraph.h"
//int main()
//{
//    linkedWDigraph<int> a(6);
//    edge<int> e1(1, 2, 1);
//    edge<int> e2(1, 3, 12);
//    edge<int> e3(2, 3, 9);
//    edge<int> e4(2, 4, 3);
//    edge<int> e5(4, 3, 4);
//    edge<int> e6(3, 5, 5);
//    edge<int> e7(4, 5, 13);
//    edge<int> e8(4, 6, 15);
//    edge<int> e9(5, 6, 4);
//    a.insertEdge(&e1);
//    a.insertEdge(&e2);
//    a.insertEdge(&e3);
//    a.insertEdge(&e4);
//    a.insertEdge(&e5);
//    a.insertEdge(&e6);
//    a.insertEdge(&e7);
//    a.insertEdge(&e8);
//    a.insertEdge(&e9);
//    std::cout << "The number of vertices is: " << a.numberOfVertices() << std::endl;
//    std::cout << "The number of edges is: " << a.numberOfEdges() << std::endl;
//    std::cout << "The indegree of vertex 4 is :" << a.inDegree(4) << std::endl;
//    std::cout << "The outdegree of vertex 4 is :" << a.outDegree(4) << std::endl;
//    std::cout << (a.existsEdge(5, 6) ? "The edge existed" : "The edge not existed") << std::endl;
//    std::cout << (a.existsEdge(6, 5) ? "The edge existed" : "The edge not existed") << std::endl;
//    a.eraseEdge(5, 6);
//    std::cout << (a.existsEdge(5, 6) ? "The edge existed" : "The edge not existed") << std::endl;
//    std::cout << "The number of edges is: " << a.numberOfEdges() << std::endl;
//    a.insertEdge(&e9);
//    auto result = a.dijkstraAlgorithm(1, 10000);
//    std::cout << "done" << std::endl;
//}


#include "graph/linkedWGraph.h"
int main()
{
    linkedWGraph<int> a(6);
    edge<int> e1(1, 2, 1);
    edge<int> e2(1, 3, 2);
    edge<int> e3(2, 3, 6);
    edge<int> e4(2, 4, 11);
    edge<int> e5(4, 3, 9);
    edge<int> e6(3, 5, 13);
    edge<int> e7(4, 5, 7);
    edge<int> e8(4, 6, 3);
    edge<int> e9(5, 6, 4);
    a.insertEdge(&e1);
    a.insertEdge(&e2);
    a.insertEdge(&e3);
    a.insertEdge(&e4);
    a.insertEdge(&e5);
    a.insertEdge(&e6);
    a.insertEdge(&e7);
    a.insertEdge(&e8);
    a.insertEdge(&e9);
    std::cout << "The number of vertices is: " << a.numberOfVertices() << std::endl;
    std::cout << "The number of edges is: " << a.numberOfEdges() << std::endl;
    // std::cout << "The indegree of vertex 4 is :" << a.inDegree(4) << std::endl;
    // std::cout << "The outdegree of vertex 4 is :" << a.outDegree(4) << std::endl;
    std::cout << "The degree of vertex 4 is :" << a.degree(4) << std::endl;
    std::cout << (a.existsEdge(5, 6) ? "The edge existed" : "The edge not existed") << std::endl;
    std::cout << (a.existsEdge(6, 5) ? "The edge existed" : "The edge not existed") << std::endl;
    a.eraseEdge(5, 6);
    std::cout << (a.existsEdge(5, 6) ? "The edge existed" : "The edge not existed") << std::endl;
    std::cout << (a.existsEdge(6, 5) ? "The edge existed" : "The edge not existed") << std::endl;
    std::cout << "The number of edges is: " << a.numberOfEdges() << std::endl;
    a.insertEdge(&e9);
    a.kruskal();
}

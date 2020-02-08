//
// Created by lcy19 on 2020/2/7.
//

#include "union_find.h"

unionFind::unionFind(int numOfElements)
{
    node = new unionFindNode[numOfElements + 1];
}

unionFind::~unionFind()
{
    delete [] node;
}

int unionFind::find(int theElement)
{
    // look up until the root
    int theRoot = theElement;
    while(!node[theRoot].root)
        theRoot = node[theRoot].parent;

    // decrease the path
    int currentNode = theElement;
    while(currentNode != theRoot)
    {
        int parentNode = node[currentNode].parent;
        node[currentNode].parent = theRoot;
        currentNode = parentNode;
    }
    return theRoot;
}

void unionFind::unite(int rootA, int rootB)
{
    if(node[rootA].parent < node[rootB].parent) // let tree A be the child of tree B
    {
        node[rootB].parent += node[rootA].parent;
        node[rootA].root = false;
        node[rootA].parent = rootB;
    } else
    {
        node[rootA].parent += node[rootB].parent;
        node[rootB].root = false;
        node[rootB].parent = rootA;
    }
}

bool unionFind::isInSameSet(int e1, int e2)
{
    return find(e1) == find(e2);
}

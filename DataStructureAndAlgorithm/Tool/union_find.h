//
// Created by lcy19 on 2020/2/7.
//

// The UNION-FIND algorithm

#ifndef UNION_FIND_H
#define UNION_FIND_H

struct unionFindNode {
    int parent; // The current node's parents, but when the current node means root, the parent indicates the tree weight(number of nodes)
    bool root; // The current node is or is not a root

    explicit unionFindNode() {
        parent = 1;
        root = true;
    }
};

class unionFind
{
public:
    explicit unionFind(int);
    ~unionFind();
    int find(int);
    void unite(int, int);
    bool isInSameSet(int, int);
private:
    unionFindNode* node;
};


#endif //UNION_FIND_H

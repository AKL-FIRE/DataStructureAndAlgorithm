//
// Created by lcy19 on 2020/1/31.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "../Exception/Exception.hpp"
#include "../Tool/utlity.h"
#include <algorithm>
#include <strstream>
#include <memory>
#include <vector>
#include <queue>

template <typename T>
class edge {
public:
    edge(const T& a, const T& b, double weight) : vertex1(a), vertex2(b), weight(weight) {};
    T get_vertex1() const
    {
        return vertex1;
    }
    T get_vertex2() const
    {
        return vertex2;
    }
    double get_weight() const
    {
        return weight;
    }

private:
    T vertex1, vertex2;
    double weight;
};

template <typename T>
class vertexIterator{
public:
    virtual ~vertexIterator() = default;
    virtual int next() = 0;
    virtual int next(T&) = 0;
};

template <typename T>
class graph {
public:
    virtual ~graph() = default;

    virtual int numberOfVertices() const = 0;
    virtual int numberOfEdges() const = 0;
    virtual bool existsEdge(int, int) const = 0;
    virtual void insertEdge(edge<T>*) = 0;
    virtual void eraseEdge(int, int) = 0;
    virtual int degree(int) const = 0;
    virtual int inDegree(int) const = 0;
    virtual int outDegree(int) const = 0;

    virtual bool directed() const = 0;
    virtual bool weighted() const = 0;
    // virtual vertexIterator<T>* iterator(int) = 0;
    virtual std::shared_ptr<vertexIterator<T>> iterator(int) = 0;
};


#endif //GRAPH_H

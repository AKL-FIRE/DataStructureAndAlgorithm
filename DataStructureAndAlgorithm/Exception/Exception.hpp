//
//  Exception.hpp
//  DataStructureAndAlgorithm
//
//  Created by Apple  on 23/01/2018.
//  Copyright © 2018 lcy. All rights reserved.
//

#ifndef Exception_hpp
#define Exception_hpp

#include <iostream>
#include <string>
#include <strstream>

class exception
{
public:
    virtual ~exception() {};
    virtual void print() const = 0;
};

class illegalParameterValue : public exception
{
public:
    virtual ~illegalParameterValue() {};
    illegalParameterValue(const char *str) : msg(str) {print();}
    illegalParameterValue(std::string &str) : msg(str) {print();}
    illegalParameterValue(std::strstream &str) : msg(str.str()) {print();}
    virtual void print() const {std::cout << msg << std::endl;}
private:
    std::string msg;
};


#endif /* Exception_hpp */

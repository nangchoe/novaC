#pragma once
#include <string>

struct Node{

    virtual ~Node(){}

};

struct VariableNode : Node{

    std::string name;
    std::string value;

};

struct PrintNode : Node{

    std::string value;

};

struct IfNode : Node{

    std::string condition;

};
#pragma once
#include <string>
#include <vector>

struct Node{

};

struct FunctionNode : Node{

    std::string name;
    std::vector<std::string> args;

};

struct VariableNode : Node{

    std::string name;
    std::string value;

};
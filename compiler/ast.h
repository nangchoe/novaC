#pragma once
#include <string>
#include <vector>

struct Node{

    virtual ~Node(){}

};

struct ProgramNode : Node{

    std::vector<Node*> statements;

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

struct BinaryExprNode : Node{

    std::string left;
    std::string op;
    std::string right;

};

struct IoOutNode : Node{

    std::string pin;
    std::string value;

};

struct ServerStartNode : Node{

};

struct FunctionNode : Node{

    std::string name;
    std::vector<std::string> args;

};

struct IfNode : Node{

    std::string left;
    std::string op;
    std::string right;

};

struct LoopNode : Node{

};
#pragma once
#include <string>
#include <vector>

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

struct StringNode : Node{

    std::string value;

};

struct IoOutNode : Node{

    std::string pin;
    std::string value;

};

struct ServerStartNode : Node{

};

struct IfNode : Node{

    std::string left;
    std::string op;
    std::string right;

};

struct LoopNode : Node{

};

struct FunctionNode : Node{

    std::string name;
    std::vector<std::string> args;

};

struct TimerNode : Node{

    std::string value;

};

struct InterruptNode : Node{

    std::string pin;

};
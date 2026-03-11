#pragma once
#include <vector>
#include "token.h"
#include "ast.h"

class Parser{

public:

    std::vector<Token> tokens;
    int pos = 0;

    Parser(){}

    std::vector<Node*> parse(std::vector<Token> t);

private:

    Token peek();
    Token advance();
    bool match(std::string v);

    Node* parseStatement();
    Node* parseVariable();
    Node* parseIf();
    Node* parseLoop();
    Node* parseCall();

};
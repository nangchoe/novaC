#pragma once
#include "lexer.h"
#include "ast.h"

#include <vector>

class Parser{

public:

    std::vector<Node*> parse(std::vector<Token> tokens);

};
#pragma once
#include <vector>
#include <string>
#include "token.h"

class Lexer{

public:

    std::vector<Token> tokenize(std::string code);

};
#include "lexer.h"
#include <sstream>
#include <cctype>

std::vector<Token> Lexer::tokenize(std::string code){

    std::vector<Token> tokens;

    std::stringstream ss(code);
    std::string word;

    while(ss >> word){

        if(word == "fn")
            tokens.push_back({TOKEN_FN,word});

        else if(word == "let")
            tokens.push_back({TOKEN_LET,word});

        else if(word == "return")
            tokens.push_back({TOKEN_RETURN,word});

        else if(isdigit(word[0]))
            tokens.push_back({TOKEN_NUMBER,word});

        else
            tokens.push_back({TOKEN_IDENTIFIER,word});
    }

    return tokens;
}
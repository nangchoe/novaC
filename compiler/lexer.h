#pragma once
#include <string>
#include <vector>

enum TokenType{

    TOKEN_FN,
    TOKEN_LET,
    TOKEN_RETURN,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,

    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_COMMA,
    TOKEN_EQUAL,

    TOKEN_UNKNOWN

};

struct Token{

    TokenType type;
    std::string value;

};

class Lexer{

public:

    std::vector<Token> tokenize(std::string code);

};
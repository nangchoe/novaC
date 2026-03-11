#pragma once
#include <string>

enum TokenType
{

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

    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,

    TOKEN_COLON,

    TOKEN_UNKNOWN

};

struct Token
{

    TokenType type;
    std::string value;
};
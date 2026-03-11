#include <iostream>
#include <cctype>
#include <string>

enum TokenType {
    TOKEN_EOF,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_LET,
    TOKEN_FN
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {

private:

    std::string source;
    int pos;

public:

    Lexer(std::string src) {
        source = src;
        pos = 0;
    }

    char peek() {
        if(pos >= source.size()) return '\0';
        return source[pos];
    }

    char advance() {
        return source[pos++];
    }

    Token nextToken() {

        while(isspace(peek())) advance();

        if(isalpha(peek())) {

            std::string ident;

            while(isalnum(peek())) {
                ident += advance();
            }

            if(ident == "let")
                return {TOKEN_LET, ident};

            if(ident == "fn")
                return {TOKEN_FN, ident};

            return {TOKEN_IDENTIFIER, ident};
        }

        if(isdigit(peek())) {

            std::string num;

            while(isdigit(peek())) {
                num += advance();
            }

            return {TOKEN_NUMBER, num};
        }

        if(peek() == '\0')
            return {TOKEN_EOF,""};

        advance();
        return {TOKEN_EOF,""};
    }

};
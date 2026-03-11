#include "lexer.h"
#include <cctype>

std::vector<Token> Lexer::tokenize(std::string code)
{

    std::vector<Token> tokens;

    int i = 0;

    while (i < code.size())
    {

        char c = code[i];

        if (isspace(c))
        {
            i++;
            continue;
        }

        // identifier / keyword
        if (isalpha(c))
        {

            std::string word;

            while (i < code.size() &&
                   (isalnum(code[i]) || code[i] == '.'))
            {

                word += code[i];
                i++;
            }

            if (word == "fn")
                tokens.push_back({TOKEN_FN, word});
            else if (word == "let")
                tokens.push_back({TOKEN_LET, word});
            else if (word == "return")
                tokens.push_back({TOKEN_RETURN, word});
            else
                tokens.push_back({TOKEN_IDENTIFIER, word});

            continue;
        }

        // number
        if (isdigit(c))
        {

            std::string num;

            while (i < code.size() && isdigit(code[i]))
            {
                num += code[i];
                i++;
            }

            tokens.push_back({TOKEN_NUMBER, num});
            continue;
        }

        if (c == '(')
        {
            tokens.push_back({TOKEN_LPAREN, "("});
            i++;
            continue;
        }
        if (c == ')')
        {
            tokens.push_back({TOKEN_RPAREN, ")"});
            i++;
            continue;
        }
        if (c == '{')
        {
            tokens.push_back({TOKEN_LBRACE, "{"});
            i++;
            continue;
        }
        if (c == '}')
        {
            tokens.push_back({TOKEN_RBRACE, "}"});
            i++;
            continue;
        }

        if (c == '+')
        {
            tokens.push_back({TOKEN_PLUS, "+"});
            i++;
            continue;
        }
        if (c == '-')
        {
            tokens.push_back({TOKEN_MINUS, "-"});
            i++;
            continue;
        }
        if (c == '*')
        {
            tokens.push_back({TOKEN_STAR, "*"});
            i++;
            continue;
        }
        if (c == '/')
        {
            tokens.push_back({TOKEN_SLASH, "/"});
            i++;
            continue;
        }

        // if(c=='='){ tokens.push_back({TOKEN_EQUAL,"="}); i++; continue; }

        if (c == ',')
        {
            tokens.push_back({TOKEN_EQUAL, "="});
            i++;
            continue;
        }

        if (c == '"')
        {

            i++;

            std::string str;

            while (i < code.size() && code[i] != '"')
            {
                str += code[i];
                i++;
            }

            i++;

            tokens.push_back({TOKEN_STRING, str});

            continue;
        }

        if (c == '=')
        {
            tokens.push_back({TOKEN_EQUAL, "="});
            i++;
            continue;
        }

        if (c == '[')
        {
            tokens.push_back({TOKEN_LBRACKET, "["});
            i++;
            continue;
        }

        if (c == ']')
        {
            tokens.push_back({TOKEN_RBRACKET, "]"});
            i++;
            continue;
        }

        if (c == ',')
        {
            tokens.push_back({TOKEN_COMMA, ","});
            i++;
            continue;
        }

        i++;
    }

    return tokens;
}
#include "parser.h"

std::vector<Node*> Parser::parse(std::vector<Token> tokens){

    std::vector<Node*> nodes;

    for(int i=0;i<tokens.size();i++){

        // let
        if(tokens[i].type == TOKEN_LET){

            VariableNode* v = new VariableNode;

            v->name = tokens[i+1].value;

            std::string expr = tokens[i+3].value;

            if(i+5 < tokens.size() &&
               (tokens[i+4].type == TOKEN_PLUS ||
                tokens[i+4].type == TOKEN_MINUS ||
                tokens[i+4].type == TOKEN_STAR ||
                tokens[i+4].type == TOKEN_SLASH)){

                expr += " " + tokens[i+4].value + " " + tokens[i+5].value;
            }

            v->value = expr;

            nodes.push_back(v);
        }

        // io.print
        if(tokens[i].type == TOKEN_IDENTIFIER &&
           tokens[i].value == "io.print"){

            PrintNode* p = new PrintNode;

            p->value = tokens[i+2].value;

            nodes.push_back(p);
        }

    }

    return nodes;
}
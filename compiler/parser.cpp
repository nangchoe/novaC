#include "parser.h"

std::vector<Node*> Parser::parse(std::vector<Token> tokens){

    std::vector<Node*> nodes;

    for(int i=0;i<tokens.size();i++){

        if(tokens[i].type == TOKEN_LET){

            VariableNode* v = new VariableNode;

            v->name = tokens[i+1].value;
            v->value = tokens[i+3].value;

            nodes.push_back(v);
        }

    }

    return nodes;
}
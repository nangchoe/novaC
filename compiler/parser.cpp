#include "parser.h"

std::vector<Node*> Parser::parse(std::vector<Token> tokens){

    std::vector<Node*> nodes;

    for(int i=0;i<tokens.size();i++){

        // let x = 10
        if(tokens[i].type == TOKEN_LET){

            VariableNode* v = new VariableNode;

            v->name = tokens[i+1].value;

            v->value = tokens[i+3].value;

            nodes.push_back(v);
        }

        // io.print(x)
        if(tokens[i].value == "io.print"){

            PrintNode* p = new PrintNode;

            p->value = tokens[i+2].value;

            nodes.push_back(p);
        }

        // if x > 10
        if(tokens[i].value == "if"){

            IfNode* n = new IfNode;

            n->condition = tokens[i+1].value;

            nodes.push_back(n);
        }

    }

    return nodes;
}
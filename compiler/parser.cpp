#include "parser.h"

std::vector<Node*> Parser::parse(std::vector<Token> tokens){

    std::vector<Node*> nodes;

    for(int i=0;i<tokens.size();i++){

        // let x = 10
        if(tokens[i].type == TOKEN_LET){

            if(i + 3 < tokens.size()){

                VariableNode* v = new VariableNode;

                v->name  = tokens[i+1].value;
                v->value = tokens[i+3].value;

                nodes.push_back(v);
            }
        }

        // io.print(x)  -> token dạng "io.print(x)"
        if(tokens[i].value.find("io.print(") == 0){

            std::string token = tokens[i].value;

            auto start = token.find("(");
            auto end   = token.find(")");

            if(start != std::string::npos && end != std::string::npos){

                PrintNode* p = new PrintNode;

                p->value = token.substr(start+1, end-start-1);

                nodes.push_back(p);
            }
        }

    }

    return nodes;
}
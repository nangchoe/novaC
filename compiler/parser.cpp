#include "parser.h"

std::vector<Node *> Parser::parse(std::vector<Token> tokens)
{

    std::vector<Node *> nodes;

    for (int i = 0; i < tokens.size(); i++)
    {

        if (tokens[i].type == TOKEN_LET)
        {

            VariableNode *v = new VariableNode;

            v->name = tokens[i + 1].value;

            std::string expr = tokens[i + 3].value;

            if (i + 5 < tokens.size())
            {

                if (tokens[i + 4].type == TOKEN_PLUS ||
                    tokens[i + 4].type == TOKEN_MINUS ||
                    tokens[i + 4].type == TOKEN_STAR ||
                    tokens[i + 4].type == TOKEN_SLASH)
                {

                    expr += " " + tokens[i + 4].value + " " + tokens[i + 5].value;
                }
            }

            v->value = expr;

            nodes.push_back(v);
        }

        if (tokens[i].type == TOKEN_IDENTIFIER &&
            tokens[i].value == "io.print")
        {

            PrintNode *p = new PrintNode;

            p->value = tokens[i + 2].value;

            nodes.push_back(p);
        }

        // io.out(pin,value)

        if (tokens[i].type == TOKEN_IDENTIFIER &&
            tokens[i].value == "io.out")
        {

            IoOutNode *n = new IoOutNode;

            n->pin = tokens[i + 2].value;
            n->value = tokens[i + 4].value;

            nodes.push_back(n);
        }

        // server.start()

        if (tokens[i].type == TOKEN_IDENTIFIER &&
            tokens[i].value == "server.start")
        {

            ServerStartNode *n = new ServerStartNode;

            nodes.push_back(n);
        }
    }

    return nodes;
}
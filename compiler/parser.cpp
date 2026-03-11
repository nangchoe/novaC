#include "parser.h"

Token Parser::peek()
{

    if (pos < tokens.size())
        return tokens[pos];

    return Token();
}

Token Parser::advance()
{

    if (pos < tokens.size())
        return tokens[pos++];

    return Token();
}

bool Parser::match(std::string v)
{

    if (peek().value == v)
    {
        advance();
        return true;
    }

    return false;
}

std::vector<Node *> Parser::parse(std::vector<Token> t)
{

    tokens = t;
    pos = 0;

    std::vector<Node *> nodes;

    while (pos < tokens.size())
    {

        int start = pos;

        Node *stmt = parseStatement();

        if (stmt)
        {
            nodes.push_back(stmt);
        }

        if (pos == start)
        {
            advance();
        }
    }

    return nodes;
}

Node *Parser::parseStatement()
{

    Token t = peek();

    if (t.value == "let")
        return parseVariable();

    if (t.value == "if")
        return parseIf();

    if (t.value == "loop")
        return parseLoop();

    if (t.value == "io.print")
        return parseCall();

    if (t.value == "io.out")
        return parseCall();

    if (t.value == "timer.delay")
        return parseCall();

    if (t.value == "interrupt.attach")
        return parseCall();

    if (t.value == "server.start")
        return parseCall();

    if (t.value == "server.get")
        return parseCall();

    if (t.value == "server.post")
        return parseCall();

    return nullptr;
}

Node *Parser::parseVariable()
{

    advance(); // let

    Token nameToken = advance();
    std::string name = nameToken.value;

    advance(); // =

    Token valueToken = advance();

    // JSON
    if (valueToken.value == "json")
    {

        advance(); // {

        JsonNode *j = new JsonNode;

        j->name = name;

        while (peek().value != "}")
        {

            std::string key = advance().value;

            advance(); // :

            std::string value = advance().value;

            j->keys.push_back(key);
            j->values.push_back(value);

            if (peek().value == ",")
                advance();
        }

        advance(); // }

        return j;
    }

    // ARRAY
    if (valueToken.value == "[")
    {

        ArrayNode *arr = new ArrayNode;

        arr->name = name;

        while (peek().value != "]")
        {

            arr->values.push_back(advance().value);

            if (peek().value == ",")
                advance();
        }

        advance(); // ]

        return arr;
    }

    // NORMAL VARIABLE
    VariableNode *v = new VariableNode;

    v->name = name;
    v->value = valueToken.value;

    return v;
}

Node *Parser::parseIf()
{

    advance(); // if

    IfNode *n = new IfNode;

    n->left = advance().value;
    n->op = advance().value;
    n->right = advance().value;

    return n;
}

Node *Parser::parseLoop()
{

    advance(); // loop

    LoopNode *l = new LoopNode;

    return l;
}

Node *Parser::parseCall()
{

    Token t = advance();

    if (t.value == "io.print")
    {

        PrintNode *p = new PrintNode;

        advance(); // (
        p->value = advance().value;
        advance(); // )

        return p;
    }

    if (t.value == "server.start")
    {

        ServerStartNode *s = new ServerStartNode;

        advance(); // (

        Token portToken = advance();

        s->port = portToken.value;

        advance(); // )

        return s;
    }

    if (t.value == "io.out")
    {

        IoOutNode *n = new IoOutNode;

        advance(); // (
        n->pin = advance().value;

        advance(); // ,
        n->value = advance().value;

        advance(); // )

        return n;
    }

    if (t.value == "timer.delay")
    {

        TimerNode *n = new TimerNode;

        advance(); // (
        n->value = advance().value;
        advance(); // )

        return n;
    }

    if (t.value == "interrupt.attach")
    {

        InterruptNode *n = new InterruptNode;

        advance(); // (
        n->pin = advance().value;
        advance(); // )

        return n;
    }

    if (t.value == "server.get")
    {

        ServerGetNode *n = new ServerGetNode;

        advance(); // (

        n->route = advance().value; // STRING

        advance(); // )

        return n;
    }

    if (t.value == "server.post")
    {

        ServerPostNode *n = new ServerPostNode;

        advance(); // (

        n->route = advance().value;

        advance(); // )

        return n;
    }

    return nullptr;
}
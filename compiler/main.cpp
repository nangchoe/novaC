#include <iostream>
#include <fstream>

#include "lexer.h"
#include "parser.h"

int main(int argc,char** argv){

    if(argc < 2){

        std::cout<<"NovaC compiler\n";
        std::cout<<"usage: novac file.nc\n";

        return 0;
    }

    std::ifstream f(argv[1]);

    std::string code(
        (std::istreambuf_iterator<char>(f)),
        std::istreambuf_iterator<char>()
    );

    Lexer lexer;

    auto tokens = lexer.tokenize(code);

    Parser parser;

    auto ast = parser.parse(tokens);

    std::cout<<"Tokens: "<<tokens.size()<<std::endl;
    std::cout<<"AST nodes: "<<ast.size()<<std::endl;

}
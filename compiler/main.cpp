#include <iostream>
#include <fstream>

#include "lexer.h"
#include "parser.h"
#include "codegen.h"

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

    Codegen gen;

    std::string ccode = gen.generate(ast);

    std::ofstream out("output.c");

    out << ccode;

    out.close();

    system("gcc output.c -o output");

    std::cout<<"Build success\n";
}
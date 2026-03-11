#include <iostream>
#include <fstream>
#include <filesystem>

#include "lexer.h"
#include "parser.h"
#include "codegen.h"

bool build(std::string file){

    std::ifstream f(file);

    if(!f){
        std::cout<<"Cannot open file\n";
        return false;
    }

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

    // std::ofstream out("output.c");
    std::ofstream out("output.cpp");
    out << ccode;
    out.close();

    // system("gcc output.c -o output.exe");
    system("g++ output.cpp -lws2_32 -o output.exe");
    // std::ofstream out("output.cpp");

    std::cout<<"Build success\n";

    return true;
}

void run(std::string file){

    if(build(file)){
        system("output.exe");
    }

}

void help(){

    std::cout<<"NovaC CLI\n";
    std::cout<<"Commands:\n";
    std::cout<<" novac build file.nc\n";
    std::cout<<" novac run file.nc\n";
}

int main(int argc,char** argv){

    if(argc < 3){

        help();
        return 0;
    }

    std::string cmd = argv[1];

    if(cmd == "build")
        build(argv[2]);

    else if(cmd == "run")
        run(argv[2]);

}
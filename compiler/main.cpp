#include <iostream>
#include <fstream>
#include <filesystem>

#include "lexer.h"
#include "parser.h"
#include "codegen.h"

void build(std::string file){

    std::ifstream f(file);

    if(!f){
        std::cout << "Cannot open file\n";
        return;
    }

    std::cout << "Reading file: " << file << std::endl;

    std::string code(
        (std::istreambuf_iterator<char>(f)),
        std::istreambuf_iterator<char>()
    );

    std::cout << "SOURCE:\n";
    std::cout << code << std::endl;

    Lexer lexer;
    auto tokens = lexer.tokenize(code);

    for(auto &t : tokens){
        std::cout << "TOKEN: " << t.value << std::endl;
    }

    Parser parser;
    auto ast = parser.parse(tokens);

    Codegen gen;

    std::string ccode = gen.generate(ast);

    std::ofstream out("output.c");
    out << ccode;
    out.close();

    system("gcc output.c -o output.exe");

    std::cout<<"Build success\n";
}

void run(std::string file){

    build(file);

    system("output.exe");
}

void newProject(std::string name){

    std::filesystem::create_directory(name);
    std::filesystem::create_directory(name + "/src");

    std::ofstream mainFile(name + "/src/main.nc");

    mainFile <<
R"(fn main(){

    let x = 10

    io.print(x)

})";

    mainFile.close();

    std::cout<<"Project created: "<<name<<"\n";
}

void help(){

    std::cout<<"NovaC CLI\n\n";

    std::cout<<"Commands:\n";
    std::cout<<"  novac build file.nc\n";
    std::cout<<"  novac run file.nc\n";
    std::cout<<"  novac new project\n";
    std::cout<<"  novac version\n";
    std::cout<<"  novac help\n";
}

void version(){

    std::cout<<"NovaC version 0.8\n";
}

int main(int argc,char** argv){

    if(argc < 2){

        help();
        return 0;
    }

    std::string cmd = argv[1];

    if(cmd == "build"){

        build(argv[2]);

    }
    else if(cmd == "run"){

        run(argv[2]);

    }
    else if(cmd == "new"){

        newProject(argv[2]);

    }
    else if(cmd == "version"){

        version();

    }
    else if(cmd == "help"){

        help();

    }
}
#include <iostream>
#include <fstream>
#include "transpiler.h"

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

    Transpiler t;

    std::string c_code = t.transpile(code);

    std::ofstream out("output.c");

    out << c_code;

    out.close();

    system("gcc output.c -o output");

    std::cout<<"Build success\n";

}
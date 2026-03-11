#include "transpiler.h"
#include <sstream>
#include <string>
#include <algorithm>

std::string trim(std::string s){

    s.erase(0,s.find_first_not_of(" \t"));
    s.erase(s.find_last_not_of(" \t")+1);

    return s;
}

std::string Transpiler::transpile(std::string code){

    std::stringstream output;

    output << "#include <stdio.h>\n";
    output << "int main(){\n";

    std::stringstream ss(code);
    std::string line;

    while(std::getline(ss,line)){

        line = trim(line);

        // skip fn main and braces
        if(line.find("fn main") != std::string::npos) continue;
        if(line == "{") continue;
        if(line == "}") continue;

        // handle let
        if(line.find("let ") == 0){

            // remove 'let '
            line = line.substr(4);

            auto eq = line.find("=");

            std::string name = trim(line.substr(0,eq));
            std::string value = trim(line.substr(eq+1));

            output << "int " << name << " = " << value << ";\n";

            continue;
        }

        // handle print
        if(line.find("io.print") != std::string::npos){

            auto start = line.find("(");
            auto end = line.find(")");

            std::string content = line.substr(start+1,end-start-1);

            output << "printf(\"%d\\n\"," << content << ");\n";

            continue;
        }

    }

    output << "return 0;\n";
    output << "}";

    return output.str();
}
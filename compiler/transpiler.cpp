#include "transpiler.h"
#include "utils.h"

#include <sstream>
#include <string>
#include <vector>

std::string buildArgs(std::string args){

    std::stringstream ss(args);
    std::string token;

    std::stringstream result;

    bool first = true;

    while(std::getline(ss,token,',')){

        token = trim(token);

        if(!first)
            result << ", ";

        result << "int " << token;

        first = false;
    }

    return result.str();
}

std::string Transpiler::transpile(std::string code){

    std::stringstream functions;
    std::stringstream mainCode;

    bool insideFunction = false;

    std::stringstream ss(code);
    std::string line;

    while(std::getline(ss,line)){

        line = trim(line);

        if(line.empty()) continue;

        // FUNCTION
        if(line.find("fn ") == 0 && line.find("main") == std::string::npos){

            auto nameStart = 3;
            auto paren = line.find("(");

            std::string fname = line.substr(nameStart,paren-nameStart);

            auto close = line.find(")");

            std::string args = line.substr(paren+1,close-paren-1);

            std::string cArgs = buildArgs(args);

            functions << "int " << fname << "(" << cArgs << "){\n";

            insideFunction = true;

            continue;
        }

        // MAIN
        if(line.find("fn main") != std::string::npos){

            mainCode << "int main(){\n";

            continue;
        }

        if(line == "{") continue;

        if(line == "}"){

            if(insideFunction){
                functions << "}\n";
                insideFunction = false;
            }else{
                mainCode << "}\n";
            }

            continue;
        }

        // RETURN
        if(line.find("return") == 0){

            std::string val = trim(line.substr(6));

            if(insideFunction)
                functions << "return " << val << ";\n";
            else
                mainCode << "return " << val << ";\n";

            continue;
        }

        // VARIABLE
        if(line.find("let ") == 0){

            line = line.substr(4);

            auto eq = line.find("=");

            std::string name = trim(line.substr(0,eq));
            std::string value = trim(line.substr(eq+1));

            mainCode << "int " << name << " = " << value << ";\n";

            continue;
        }

        // PRINT
        if(line.find("io.print") != std::string::npos){

            auto start = line.find("(");
            auto end = line.find(")");

            std::string content = trim(line.substr(start+1,end-start-1));

            if(content.find("\"") != std::string::npos)
                mainCode << "printf(\"%s\\n\"," << content << ");\n";
            else
                mainCode << "printf(\"%d\\n\"," << content << ");\n";

            continue;
        }

    }

    std::stringstream final;

    final << "#include <stdio.h>\n";
    final << functions.str();
    final << mainCode.str();

    return final.str();
}
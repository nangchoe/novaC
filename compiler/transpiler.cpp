#include "transpiler.h"
#include "utils.h"

#include <sstream>
#include <string>

std::string Transpiler::transpile(std::string code){

    std::stringstream output;

    int blockDepth = 0;

    output << "#include <stdio.h>\n";
    output << "int main(){\n";

    std::stringstream ss(code);
    std::string line;

    while(std::getline(ss,line)){

        line = trim(line);

        if(line.empty()) continue;

        if(line.find("fn main") != std::string::npos) continue;

        if(line == "{" || line == "}") continue;

        // let variable
        if(line.find("let ") == 0){

            line = line.substr(4);

            auto eq = line.find("=");

            std::string name = trim(line.substr(0,eq));
            std::string value = trim(line.substr(eq+1));

            output << "int " << name << " = " << value << ";\n";

            continue;
        }

        // if
        if(line.find("if ") == 0){

            std::string cond = line.substr(3);

            auto brace = cond.find("{");

            if(brace != std::string::npos)
                cond = trim(cond.substr(0,brace));

            output << "if(" << cond << "){\n";

            blockDepth++;

            continue;
        }

        // loop
        if(line.find("loop") == 0){

            output << "while(1){\n";

            blockDepth++;

            continue;
        }

        // print
        if(line.find("io.print") != std::string::npos){

            auto start = line.find("(");
            auto end = line.find(")");

            std::string content = trim(line.substr(start+1,end-start-1));

            // detect string
            if(content.find("\"") != std::string::npos){

                output << "printf(\"%s\\n\"," << content << ");\n";

            } else {

                output << "printf(\"%d\\n\"," << content << ");\n";

            }

            continue;
        }

    }

    while(blockDepth > 0){
        output << "}\n";
        blockDepth--;
    }

    output << "return 0;\n";
    output << "}\n";

    return output.str();
}
#include "transpiler.h"
#include "utils.h"

#include <sstream>
#include <string>
#include <vector>

struct Arg{

    std::string name;
    std::string def;
};

struct FunctionInfo{

    std::string name;
    std::vector<Arg> args;
};

std::vector<FunctionInfo> functionsList;

std::vector<Arg> parseArgs(std::string args){

    std::vector<Arg> result;

    std::stringstream ss(args);
    std::string token;

    while(std::getline(ss,token,',')){

        token = trim(token);

        Arg a;

        auto eq = token.find("=");

        if(eq != std::string::npos){

            a.name = trim(token.substr(0,eq));
            a.def = trim(token.substr(eq+1));

        }else{

            a.name = token;
            a.def = "";

        }

        result.push_back(a);
    }

    return result;
}

std::string buildArgs(std::vector<Arg> args){

    std::stringstream out;

    bool first = true;

    for(auto &a:args){

        if(!first)
            out << ", ";

        out << "int " << a.name;

        first = false;
    }

    return out.str();
}

FunctionInfo* findFunction(std::string name){

    for(auto &f:functionsList){

        if(f.name == name)
            return &f;
    }

    return nullptr;
}

std::string applyDefaultArgs(std::string name,std::string args){

    FunctionInfo* f = findFunction(name);

    if(!f) return name + "(" + args + ")";

    std::vector<std::string> given;

    std::stringstream ss(args);
    std::string token;

    while(std::getline(ss,token,',')){

        given.push_back(trim(token));
    }

    std::stringstream finalArgs;

    for(int i=0;i<f->args.size();i++){

        if(i < given.size()){

            finalArgs << given[i];

        }else{

            finalArgs << f->args[i].def;

        }

        if(i != f->args.size()-1)
            finalArgs << ",";
    }

    return name + "(" + finalArgs.str() + ")";
}

std::string Transpiler::transpile(std::string code){

    std::stringstream functions;
    std::stringstream mainCode;

    bool insideFunction = false;

    std::string currentFunction;

    std::stringstream ss(code);
    std::string line;

    while(std::getline(ss,line)){

        line = trim(line);

        if(line.empty()) continue;

        // FUNCTION
        if(line.find("fn ") == 0 && line.find("main") == std::string::npos){

            auto nameStart = 3;
            auto paren = line.find("(");

            currentFunction = trim(line.substr(nameStart,paren-nameStart));

            auto close = line.find(")");

            std::string argText = line.substr(paren+1,close-paren-1);

            std::vector<Arg> args = parseArgs(argText);

            FunctionInfo fi;
            fi.name = currentFunction;
            fi.args = args;

            functionsList.push_back(fi);

            std::string cArgs = buildArgs(args);

            functions << "int " << currentFunction << "(" << cArgs << "){\n";

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

            functions << "return " << val << ";\n";

            continue;
        }

        // VARIABLE
        if(line.find("let ") == 0){

            line = line.substr(4);

            auto eq = line.find("=");

            std::string name = trim(line.substr(0,eq));
            std::string value = trim(line.substr(eq+1));

            // detect function call
            auto paren = value.find("(");

            if(paren != std::string::npos){

                auto close = value.find(")");

                std::string fname = value.substr(0,paren);

                std::string args = value.substr(paren+1,close-paren-1);

                value = applyDefaultArgs(fname,args);
            }

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
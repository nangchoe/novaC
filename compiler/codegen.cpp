#include "codegen.h"
#include <sstream>

std::string Codegen::generate(std::vector<Node*> nodes){

    std::stringstream out;

    out << "#include <stdio.h>\n";
    out << "#include \"runtime/server.h\"\n\n";

    out << "int main(){\n";

    for(auto node : nodes){

        if(auto s = dynamic_cast<ServerStartNode*>(node)){
            out << "Server::start(8080);\n";
        }

        if(auto p = dynamic_cast<PrintNode*>(node)){
            out << "printf(\"%s\\n\",\"" << p->value << "\");\n";
        }

    }

    out << "return 0;\n";
    out << "}\n";

    return out.str();
}
#include "codegen.h"
#include <sstream>

std::string Codegen::generate(std::vector<Node*> ast){

    std::stringstream out;

    out << "#include <stdio.h>\n";
    out << "int main(){\n";

    for(auto node : ast){

        if(auto v = dynamic_cast<VariableNode*>(node)){

            out << "int " << v->name << " = " << v->value << ";\n";

        }

        if(auto p = dynamic_cast<PrintNode*>(node)){

            if(p->value.find("\"") != std::string::npos)
                out << "printf(\"%s\\n\"," << p->value << ");\n";
            else
                out << "printf(\"%d\\n\"," << p->value << ");\n";

        }

        if(auto i = dynamic_cast<IfNode*>(node)){

            out << "if(" << i->condition << "){ }\n";

        }

    }

    out << "return 0;\n";
    out << "}";

    return out.str();
}
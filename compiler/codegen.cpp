#include "codegen.h"
#include <sstream>

std::string Codegen::generate(std::vector<Node *> ast)
{

    std::stringstream out;

    out << "#include <stdio.h>\n";
    out << "int main(){\n";

    for (auto node : ast)
    {

        if (auto v = dynamic_cast<VariableNode *>(node))
        {

            out << "int " << v->name << " = " << v->value << ";\n";
        }

        if (auto p = dynamic_cast<PrintNode *>(node))
        {

            if (p->value.find("\"") != std::string::npos)
                out << "printf(\"%s\\n\"," << p->value << ");\n";
            else
                out << "printf(\"%d\\n\"," << p->value << ");\n";
        }

        if (auto io = dynamic_cast<IoOutNode *>(node))
        {

            out << "printf(\"GPIO %d -> %d\\n\","
                << io->pin << ","
                << io->value << ");\n";
        }

        if (auto s = dynamic_cast<ServerStartNode *>(node))
        {

            out << "printf(\"NovaC Web Server started\\n\");\n";
        }
    }

    out << "return 0;\n";
    out << "}";

    return out.str();
}
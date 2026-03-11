#include "codegen.h"
#include <sstream>

std::string Codegen::generate(std::vector<Node *> nodes)
{

    std::stringstream out;

    out << "#include <stdio.h>\n";
    out << "#include \"runtime/server.h\"\n\n";
    out << "#include \"runtime/io.h\"\n";
    out << "#include \"runtime/timer.h\"\n";
    out << "#include \"runtime/interrupt.h\"\n";

    out << "int main(){\n";

    for (auto node : nodes)
    {

        if (auto s = dynamic_cast<ServerStartNode *>(node))
        {
            out << "Server::start("
                << s->port
                << ");\n";
        }

        if (auto p = dynamic_cast<PrintNode *>(node))
        {
            out << "printf(\"%s\\n\",\"" << p->value << "\");\n";
        }

        if (auto io = dynamic_cast<IoOutNode *>(node))
        {

            out << "IO::out("
                << io->pin << ","
                << io->value << ");\n";
        }

        if (auto t = dynamic_cast<TimerNode *>(node))
        {

            out << "Timer::delay("
                << t->value << ");\n";
        }

        if (auto i = dynamic_cast<InterruptNode *>(node))
        {

            out << "Interrupt::attach("
                << i->pin << ");\n";
        }

        if (auto io = dynamic_cast<IoOutNode *>(node))
        {

            out << "IO::out("
                << io->pin << ","
                << io->value << ");\n";
        }

        if (auto g = dynamic_cast<ServerGetNode *>(node))
        {

            out << "Server::get(\""
                << g->route
                << "\");\n";
        }

        if (auto p = dynamic_cast<PrintNode *>(node))
        {

            out << "std::cout << "
                << p->value
                << " << std::endl;\n";
        }

        if (auto v = dynamic_cast<VariableNode *>(node))
        {

            out << "auto "
                << v->name
                << " = ";

            if (v->value.size() > 0 && !isdigit(v->value[0]))
                out << "\"" << v->value << "\"";
            else
                out << v->value;

            out << ";\n";
        }

        if (auto a = dynamic_cast<ArrayNode *>(node))
        {

            out << "int "
                << a->name
                << "[] = {";

            for (int i = 0; i < a->values.size(); i++)
            {

                out << a->values[i];

                if (i < a->values.size() - 1)
                    out << ",";
            }

            out << "};\n";
        }
    }

    out << "return 0;\n";
    out << "}\n";

    return out.str();
}
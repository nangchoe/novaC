#include "codegen.h"
#include <sstream>

std::string Codegen::generate(std::vector<Node *> nodes)
{

    std::stringstream out;

    out << "#include <stdio.h>\n";
    out << "#include \"runtime/server.h\"\n\n";
    out << "int main(){\n";
    out << "#include \"runtime/io.h\"\n";
    out << "#include \"runtime/timer.h\"\n";
    out << "#include \"runtime/interrupt.h\"\n";

    for (auto node : nodes)
    {

        if (auto s = dynamic_cast<ServerStartNode *>(node))
        {
            out << "Server::start(8080);\n";
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
    }

    out << "return 0;\n";
    out << "}\n";

    return out.str();
}
#pragma once
#include "ast.h"
#include <string>
#include <vector>

class Codegen{

public:

    std::string generate(std::vector<Node*> ast);

};
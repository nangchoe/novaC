#pragma once
#include <string>

class Convert{

public:

    static int toInt(std::string v){

        return std::stoi(v);

    }

    static std::string toString(int v){

        return std::to_string(v);

    }

};
#pragma once
#include <map>
#include <string>

class Json{

public:

    std::map<std::string,std::string> data;

    void set(std::string k,std::string v){

        data[k] = v;

    }

};
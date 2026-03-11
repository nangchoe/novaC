#pragma once
#include <string>
#include <map>

class JsonEncode{

public:

    static std::string encode(std::map<std::string,std::string> data){

        std::string out = "{";

        bool first = true;

        for(auto &kv : data){

            if(!first)
                out += ",";

            out += "\"" + kv.first + "\":\"" + kv.second + "\"";

            first = false;

        }

        out += "}";

        return out;

    }

};
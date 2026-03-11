#pragma once
#include <map>
#include <string>

class DeviceState{

public:

    static std::map<std::string,std::string> state;

    static void set(std::string key,std::string value){

        state[key] = value;

    }

};
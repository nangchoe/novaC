#pragma once
#include <string>
#include <algorithm>

class String{

public:

    static int len(std::string s){

        return s.size();

    }

    static std::string upper(std::string s){

        std::transform(
            s.begin(),
            s.end(),
            s.begin(),
            ::toupper
        );

        return s;
    }

};
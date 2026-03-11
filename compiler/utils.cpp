#include "utils.h"

std::string trim(std::string s){

    s.erase(0,s.find_first_not_of(" \t"));
    s.erase(s.find_last_not_of(" \t")+1);

    return s;
}
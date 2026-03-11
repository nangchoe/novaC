#pragma once
#include <iostream>

class Server{

public:

    static void start(){

        std::cout<<"NovaC Web Server running\n";

    }

    static void get(std::string route){

        std::cout<<"GET "<<route<<"\n";

    }

    static void post(std::string route){

        std::cout<<"POST "<<route<<"\n";

    }

};
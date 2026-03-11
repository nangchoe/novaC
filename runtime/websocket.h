#pragma once
#include <iostream>

class WebSocket{

public:

    static void send(std::string msg){

        std::cout<<"WS SEND "<<msg<<"\n";

    }

};
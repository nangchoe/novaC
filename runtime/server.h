#pragma once
#include <iostream>
#include "http_server.h"

class Server{

public:

    static void start(int port){

        std::cout<<"NovaC HTTP Server starting...\n";

        HttpServer::start(port);

    }

};
#pragma once
#include <iostream>
#include "http_server.h"

class Server
{

public:
    static void start(int port)
    {

        std::cout << "NovaC HTTP Server starting...\n";

        HttpServer::start(port);
    }

    static void get(std::string route)
    {

        std::cout << "GET route registered: " << route << "\n";
    }

    static void post(std::string route)
    {

        std::cout << "POST route registered: " << route << "\n";
    }
};
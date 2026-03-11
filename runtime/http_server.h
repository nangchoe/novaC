#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <winsock2.h>

class HttpServer{

public:

    static void start(int port){

        WSADATA wsa;

        WSAStartup(MAKEWORD(2,2),&wsa);

        SOCKET server_fd;

        server_fd = socket(AF_INET,SOCK_STREAM,0);

        sockaddr_in server;

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(port);

        bind(server_fd,(sockaddr*)&server,sizeof(server));

        listen(server_fd,5);

        std::cout<<"NovaC HTTP server running on port "<<port<<"\n";

        while(true){

            SOCKET client;

            sockaddr_in client_addr;

            int c = sizeof(sockaddr_in);

            client = accept(server_fd,(sockaddr*)&client_addr,&c);

            std::thread(handle_client,client).detach();
        }

    }

    static void handle_client(SOCKET client){

        char buffer[2000];

        recv(client,buffer,2000,0);

        std::string request(buffer);

        std::cout<<"HTTP Request:\n"<<request<<"\n";

        std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n\r\n"
        "{\"status\":\"ok\"}";

        send(client,response.c_str(),response.size(),0);

        closesocket(client);

    }

};
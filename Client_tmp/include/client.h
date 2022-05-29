#pragma once

#include <netinet/in.h>
#include <string>

enum ERROR {OK = 0, FAILED_TO_CREATE_SOCKET, FAILED_TO_PARSE_IP_ADDRESS,
            FAILED_TO_CONNECT_TO_SOCKET, FAILED_TO_WRITE_DATA};

class Client {
    int fd;
    struct sockaddr_in addr;
    ERROR err = OK;

public:

    int getSocket();

    struct sockaddr_in& getSockaddr_in();

    ERROR getStatus();

    int sendMessage(std::string word);

    Client(std::string ip="127.0.0.1", std::string="8080");
};

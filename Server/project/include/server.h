#pragma once

#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <vector>

enum ERROR {OK = 0, FAILED_TO_CREATE_SOCKET, FAILED_TO_PARSE_IP_ADDRESS,
    FAILED_TO_BIND_SOCKET, FAILED_TO_START_LISTENING_SOCKET,
    FAILED_TO_ACCEPT_NEW_CONNECTION, FAILED_TO_READ_DATA_FROM_CLIENT,
    FAILED_TO_WRITE_DATA_TO_CLIENT_SOCKET};

class Server {
    int fd;
    struct sockaddr_in addr;
    ERROR status = OK;

public:
    int getSocket();

    struct sockaddr_in& getSockaddr_in();

    ERROR getStatus();

    void runServer();

    std::string getSyns(std::string inputWord);

    Server(std::string ip="127.0.0.1", std::string="8080");
    ~Server();
};
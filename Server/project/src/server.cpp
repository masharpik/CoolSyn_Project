#include "server.h"

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Server::Server(std::string ip, std::string port) {
    int rc;

    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        this->status = FAILED_TO_CREATE_SOCKET;
    }

    this->addr = { .sin_family = AF_INET };
    rc = inet_aton(ip.c_str(), &addr.sin_addr);
    if (!rc) {
        this->status = FAILED_TO_PARSE_IP_ADDRESS;
    }
    addr.sin_port = htons(std::stoi(port.c_str()));

    rc = bind(fd, (struct sockaddr*)&addr, (socklen_t)sizeof(addr));
    if (rc) {
        this->status = FAILED_TO_BIND_SOCKET;
    }

    rc = listen(fd, 1024);
    if (rc) {
        this->status = FAILED_TO_START_LISTENING_SOCKET;
    }
}

int Server::getSocket() {
    return this->fd;
}

struct sockaddr_in& Server::getSockaddr_in() {
    return this->addr;
}

ERROR Server::getStatus() {
    return this->status;
}

void Server::runServer() {
    char inputWord[1000];
    while (true) {
        try {
            int clientFd = accept(fd, NULL, NULL);
            if (clientFd == -1) {
                this->status = FAILED_TO_ACCEPT_NEW_CONNECTION;
                return;
            }

            while (true) {
                ssize_t r = read(clientFd, inputWord, sizeof(inputWord));
//                if (r == -1) {
//                    this->status = FAILED_TO_READ_DATA_FROM_CLIENT;
//                    return;
//                } else
                    if (r == 0) {
                        break;
                    }

                std::string outputWord = getSyns(std::string(inputWord));
                char cOutputWord[2000];
                cOutputWord[1999] = '\0';
                strcpy(cOutputWord, outputWord.c_str());
                ssize_t w = write(clientFd, cOutputWord, sizeof(cOutputWord));
//            if (w != sizeof(cOutputWord)) {
//                this->status = FAILED_TO_WRITE_DATA_TO_CLIENT_SOCKET;
//                return;
//            }
            }
            close(clientFd);
        } catch (const std::string& err) {
            std::cout << err << std::endl;
        }
    }
}

std::string Server::getSyns(std::string inputWord) {
    std::ifstream file("paraphrase.csv");
    std::string line;
    while (getline(file, line)) {
        std::stringstream stream(line);
        std::string item;
        std::vector<std::string> elems = {};
        while(std::getline(stream, item, ',')) {
            elems.push_back(item);
        }
        if (elems[0] == inputWord) {
            return elems[1];
        }
    }
    file.close();
}

Server::~Server() {
    close(this->fd);
}

#include "client.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

Client::Client(std::string ip, std::string port) {
    int rc = 0;

    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->fd == -1) {
        this->err = FAILED_TO_CREATE_SOCKET;
    }

    this->addr = { .sin_family = AF_INET };
    rc = inet_aton((const char*)&ip, &(this->addr.sin_addr));
    if (rc != 1) {
        this->err = FAILED_TO_PARSE_IP_ADDRESS;
    }
    addr.sin_port = htons(std::stoi(port));

    rc = connect(this->fd, (struct sockaddr*)&(this->addr), (socklen_t)sizeof(this->addr));
    if (rc) {
        this->err = FAILED_TO_CONNECT_TO_SOCKET;
    }
}

int Client::getSocket() {
    return this->fd;
}

struct sockaddr_in& Client::getSockaddr_in() {
    return this->addr;
}

ERROR Client::getStatus() {
    return this->err;
}

int Client::sendMessage(std::string word) {
    ssize_t w = write(this->fd, word.c_str(), word.size() + 1);
    if (w == -1) {
        this->err = FAILED_TO_WRITE_DATA;
    }
}

Client::~Client() {
    close(this->fd);
}

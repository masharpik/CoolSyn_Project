#include "client.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <QMessageBox>

Client::Client(Widget *win, std::string ip, std::string port) {
    this->w = win;

    int rc = 0;

    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->fd == -1) {
        this->status = FAILED_TO_CREATE_SOCKET;
    }

    this->addr = { .sin_family = AF_INET };
    rc = inet_aton(ip.c_str(), &(this->addr.sin_addr));
    if (rc != 1) {
        this->status = FAILED_TO_PARSE_IP_ADDRESS;
    }
    addr.sin_port = htons(std::stoi(port));

    rc = connect(this->fd, (struct sockaddr*)&(this->addr), (socklen_t)sizeof(this->addr));
    if (rc) {
        this->status = FAILED_TO_CONNECT_TO_SOCKET;
    }
}

int Client::getSocket() {
    return this->fd;
}

struct sockaddr_in& Client::getSockaddr_in() {
    return this->addr;
}

ERROR Client::getStatus() {
    return this->status;
}

int Client::sendMessage(std::string word) {

    ssize_t w = write(this->fd, word.c_str(), word.size() + 1);
    if (w == -1) {
        this->status = FAILED_TO_WRITE_DATA;
        return 1;
    }
    return 0;
}

QVector<QString> Client::getSyns(std::string word) {
    sendMessage(word);
    char result[1024];
    ssize_t r = read(this->fd, result, sizeof(result));
    if (r == -1) {
        this->status = FAILED_TO_READ_DATA;
    }
    if (r == 0) {
        return {};
    }
    QVector<QString> syns;
    for(QString &syn: QString::fromStdString(std::string(result)).split('|')) {
        syns.push_back(syn);
    }
    return syns;
}

Client::~Client() {
    close(this->fd);
}

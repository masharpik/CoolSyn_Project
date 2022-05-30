#pragma once

#include "synwindow.h"

#include <netinet/in.h>
#include <string>
#include <QVector>
#include <QString>

enum ERROR {OK = 0, FAILED_TO_CREATE_SOCKET, FAILED_TO_PARSE_IP_ADDRESS,
            FAILED_TO_CONNECT_TO_SOCKET, FAILED_TO_WRITE_DATA,
           FAILED_TO_READ_DATA};

class Client {
    int fd;
    struct sockaddr_in addr;
    ERROR status = OK;
    Widget *w;

    int sendMessage(std::string word);

public:

    int getSocket();

    struct sockaddr_in& getSockaddr_in();

    ERROR getStatus();

    QVector<QString> getSyns(std::string word);

    Client(Widget *wind, std::string ip="127.0.0.1", std::string="8080");
    ~Client();
};

/*  привет, это послание пользователям этого приложения!! © Бегите отсюда :3  */

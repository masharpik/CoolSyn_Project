#include "utils.h"

#include <iostream>

using std::cout;

Server::Server(const std::string &address, ip::port_type port) : host(ip::address::from_string(address), port), 
                                                                                        serv_socket(get_context()) {}

static const asio::io_context &get_context()
{
    static asio::io_context context;
    return context;
}

void Server::run()
{
    while (is_running)
    {
        auto socket = ip::tcp::iostream(serv_socket.accept());
    }
}

void Server::proccess(ip::tcp::iostream &client) {
    std::string s;
    client >> s;

    // TODO(Masha): данные, полученные в s должны дальше обрабатываться
    std::cout << "Server: " << std::endl;
    std::cout << s << std::endl;
}

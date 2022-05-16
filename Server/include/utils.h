#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <boost/asio.hpp>

namespace asio = boost::asio;
namespace ip = boost::asio::ip;

class Server {
    ip::tcp::endpoint host;
    ip::tcp::acceptor serv_socket;

    bool is_running;

    Server(const std::string &address, ip::port_type port);

    static asio::io_context& get_context();

    void run();

    void proccess(ip::tcp::iostream &client);
};

// void check_working();

#endif //SERVER_UTILS_H

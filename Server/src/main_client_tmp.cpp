// TODO(Masha): реализовать функцию передачи от клиента к серверу данных. Потом этот код прикрепить к проекту Client

#include <boost/asio.hpp>

static const asio::io_context &get_context()
{
    static asio::io_context context;
    return context;
}

void talk() {
    std::string s;
    s = "I am from client";
    boost::asio::ip:tcp::iostream socket(get_context());
    ip::tcp::endpoint host(ip::address::from_string("127.0.0.1"), 8000);
    socket.connect(host);
    socket << s;
}

int main() {
    talk();
}

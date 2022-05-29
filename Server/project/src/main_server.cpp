#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define EXIT(condition, reason) \
    if (condition) { if (errno) perror(reason); else fprintf(stderr, "%s\n", reason); return 1; }

int main(int argc, char** argv) {
    EXIT(argc != 3, "ip and port are expected");
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    EXIT(fd == -1, "failed to create socket");
    struct sockaddr_in addr = { .sin_family = AF_INET };
    EXIT(!inet_aton(argv[1], &addr.sin_addr), "failed to parse IP address");
    addr.sin_port = htons(std::stoi(argv[2]));
    EXIT(bind(fd, (struct sockaddr*)&addr, (socklen_t)sizeof(addr)), "failed to bind socket");
    EXIT(listen(fd, 1024), "failed to start listening socket");
    char buf[1024];
    bool running = true;
    while (running) {
        int client_fd = accept(fd, NULL, NULL);
        EXIT(client_fd == -1, "failed to accept new connection");
        while (running) {
            ssize_t r = read(client_fd, buf, sizeof(buf));
            EXIT(r == -1, "failed to read data from client");
            buf[r] = '\0';
            std::cout << buf << std::endl;
            if (r == 0) {
                break;
            }
            if (strcmp(buf, "exit\n") == 0) {
                running = false;
                break;
            }
            strcpy(buf, " yeah\n");
            ssize_t w = write(client_fd, buf, strlen(buf));
            EXIT(w != strlen(buf), "failed to write data to client socket");
        }
        close(client_fd);
    }
    close(fd);
}
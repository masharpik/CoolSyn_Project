#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>

#define EXIT(condition, reason) \
    if (condition) { if (errno) perror(reason); else fprintf(stderr, "%s\n", reason); exit(1); }

int main(int argc, char** argv) {
    EXIT(argc != 2, "path to socket file is expected");
    int fd = socket(AF_UNIX, SOCK_STREAM, 0);
    EXIT(fd == -1, "failed to create socket");
    struct sockaddr_un addr = { .sun_family = AF_UNIX };
    snprintf(addr.sun_path, sizeof(addr.sun_path), "%s", argv[1]);
    unlink(argv[1]);
    EXIT(bind(fd, (struct sockaddr*)&addr, (socklen_t)SUN_LEN(&addr)), "failed to bind socket");
    EXIT(listen(fd, 1024), "failed to start listening socket");
    char buf[1024];
    while (true) {
        int client_fd = accept(fd, NULL, NULL);
        EXIT(client_fd == -1, "failed to accept new connection");
        while (true) {
            ssize_t r = read(client_fd, buf, sizeof(buf)); EXIT(r == -1, "failed to read data from client");
            if (r == 0) {
                close(client_fd);
                break;
            }
            ssize_t w = write(client_fd, buf, r);
            EXIT(w != r, "failed to write data to client socket"); }
    }
}
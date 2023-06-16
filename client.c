#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct addrinfo hints, *res;
    int sockfd, status;
    char buffer[1024];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo("192.168.124.224", "5000", &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd == -1) {
        perror("socket error");
        exit(1);
    }

    status = connect(sockfd, res->ai_addr, res->ai_addrlen);
    if (status == -1) {
        perror("connect error");
        exit(1);
    }

   
    const char *message = "Hi There. I am client1\n";
    send(sockfd, message, strlen(message), 0);

    
    int bytes_received = recv(sockfd, buffer, sizeof buffer - 1, 0);
    buffer[bytes_received] = '\0';

   
    printf("%s", buffer);

    
    close(sockfd);

    return 0;
}


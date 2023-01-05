#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>

#include "listen.h"
#include "request.h"
#include "response.h"

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void handle_http_request(int sockfd) {
    
}

int main(void)
{   
    struct sockaddr_storage their_addr; 
    int listener, new_fd;
    socklen_t sin_size;
    char s[INET6_ADDRSTRLEN];
    char buf[1000];

    listener = get_listener_socket();

    if (listener == -1) {
        fprintf(stderr, "error getting listening socket\n");
        exit(1);
    }

    printf("server: waiting for connections...\n");

    while(1) {  
        sin_size = sizeof their_addr;
        new_fd = accept(listener, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("server: got connection from %s\n", s);

        handle_http_request(new_fd);

        request_handling(new_fd);

        if (send_response(new_fd, "HTTP/1.1", 200, "OK", "<h1>IT'S WORKING!</h1>", "Thu, 5 JAN 2023 14:41:00 GMT") == -1) {
            perror("send_response");
        }

        close(new_fd);  
    }

    return 0;
}
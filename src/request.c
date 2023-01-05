#include <sys/socket.h>
#include <string.h>
#include <stdio.h>

void request_handling(int sockfd) {
    char req[10000];
    char *token, *sep = " ";
    int i = 0;

    if (recv(sockfd, req, sizeof req, 0) == -1) {
        return -1;
    }
    req[1000] = '\0';

    token = strtok(req, sep);
    
    // while (token != NULL) {
    //     i++;

    //     switch (i) {
    //         case 1:
    //             handle_method(token);
    //             break;
    //         case 2:
    //             handle_URI(token);
    //             break;
    //         case 3:
    //             break;
            
    //         default: 
    //             printf("Error!");
    //             break;
    //     }

    //     token = strtok(req, sep);
    // }
    
}

void handle_method(char *str) {

    if (strcmp(str, "GET") == 0) {
                    
    } else {
        
    }
}

void handle_URI(char *str) {

}
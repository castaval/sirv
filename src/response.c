#include <string.h>
#include <sys/socket.h>
#include <stdio.h>

int sendall(int s, char *buf, int *len) {
    int total = 0;
    int bytesleft = *len;
    int n;

    while (total < *len) {
        n = send(s, buf+total, bytesleft, 0);
        if (n == -1) { break; }
        total += n;
        bytesleft -= n;
    }

    *len = total;

    return n == -1 ? -1 : 0;
}

int send_response(int sockfd, char *http_version, int http_status, char *reason_phrase, char *content, char *date) {
    char resp[1000];

    size_t content_length = strlen(content);

    sprintf(resp,  
    "%s %d %s\r\n"
    "Date: %s\r\n"
    "Content-Type: %s\r\n"
    "Content-Length: %ld\r\n"
    "\r\n"
    "%s\r\n"
    , 
    http_version, http_status, reason_phrase, date, "text/html", content_length, content);

    printf("%s", resp);

    size_t resp_len = strlen(resp);

    if (sendall(sockfd, resp, resp_len) == -1) {
        printf("We only sent %ld bytes because of the error!\n", resp_len);
        return -1;
    }

    return 0;
}
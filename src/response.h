#ifndef RESPONSE_H
#define RESPONSE_H

int send_response(int sockfd, char *http_version, int http_status, char *reason_phrase, char *content, char *date);

#endif 
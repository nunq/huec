#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "config.h"
#include "util.h"

int sockfd, n;
struct sockaddr_in servaddr;
char recvdata[MAXLINE];
//char *request;

int createSocket() {

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("socket");
  }

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port   = htons(HUE_PORT);
  if (inet_pton(AF_INET, HUE_IP_ADDR, &servaddr.sin_addr) <= 0)
    error("converting (inet_pton)");
  if (connect(sockfd, (struct servaddr *)&servaddr, sizeof(servaddr)) < 0)
    error("connecting to bridge");
  return 0;
}

int sendRequest(const char *request) {
  //request = "GET / HTTP/1.0\r\n\r\n";

  if (write(sockfd, request, strlen(request)) != strlen(request))
    error("sending data");

  while ((n = read(sockfd, recvdata, MAXLINE-1)) > 0) {
    printf("%s", recvdata);
    memset(recvdata, 0, MAXLINE);
  }
  if (n < 0)
    error("receiving data");
}

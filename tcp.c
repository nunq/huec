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

int main() {
  
  int sockfd, n;
  int sdata;
  struct sockaddr_in servaddr;
  char recdata[MAXLINE];
  char *request;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("socket");
  }

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port   = htons(HUE_PORT);

  if (inet_pton(AF_INET, HUE_IP_ADDR, &servaddr.sin_addr) <= 0)
    error("conv");

  if (connect(sockfd, (struct servaddr *)&servaddr, sizeof(servaddr)) < 0)
    error("conn");

  request = "GET / HTTP/1.0\r\n\r\n";

  if(write(sockfd, request, strlen(request)) != strlen(request))
    error("write");

  while ((n = read(sockfd, recdata, MAXLINE-1)) > 0) {
    printf("%s", recdata);
    memset(recdata, 0, MAXLINE);
  }

  if (n < 0)
    error("read");

  return 0;
}

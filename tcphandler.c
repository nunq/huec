#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "util.h"
#include "config.h"

struct sockaddr_in servaddr;
static char recvdata[4096];
static int sockfd;

int createSocket()
{
  // setup socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("socket");
  }

  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port   = htons(HUE_PORT);
  if (inet_pton(AF_INET, HUE_IP_ADDR, &servaddr.sin_addr) <= 0)
    error("converting (inet_pton)");
  if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
    error("connecting to bridge");
  return 0;
}

char *RequestHandler(const char *request)
{
  int n;
  unsigned long int w;

  // tcp communication handling
  if ( (w = write(sockfd, request, strlen(request))) != strlen(request))
    error("sending data");
  
  while ((n = read(sockfd, recvdata, 4095)) > 0) {}
  if (n < 0) {
    error("receiving data");
  }
  close(sockfd);
  return recvdata;
}

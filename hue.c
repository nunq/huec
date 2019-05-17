#include <stdio.h>

#include "tcphandler.h"
#include "config.h"
#include "privconfig.h"

int main() {

  char req[MAXLINE];
  char *action = "lights";
  createSocket();

  sprintf(req, "GET /api/%s/%s\r\n\r\n", TOKEN, action);

  sendRequest(req);

  return 0;
}

#include <stdio.h>

#include "tcphandler.h"
#include "config.h"
#include "privconfig.h"
#include "extract.h"

int main() {

  char req[MAXLINE];
  char *action = "lights";
  char *response;
  char *prop;

  createSocket();

  sprintf(req, "GET /api/%s/%s\r\n\r\n", TOKEN, action);

  if ( (response = sendRequest(req)) == "")
    error("response is empty");

  prop = getProp("on", response);

  printf("%s\n", prop);

  return 0;
}

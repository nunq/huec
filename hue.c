#include <stdio.h>

#include "comms.h"

int main() {

  printf("%s\n",  getProp(1, "on"));

  printf("%d\n", setProp("PUT", 1, "state", "on", "true"));

  close(sockfd);

  return 0;
}

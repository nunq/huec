#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

#include "comms.h"
#include "tcphandler.h"
#include "util.h"
#include "config.h"
#include "profiles.h"

void printhelp()
{
  printf("cli options:\n\
  -l  light, if not provided uses default\n\
  -p  1 (on) or 0 (off)\n\
  -b  brightness (0-254)\n\
  -c  hue (0-65535)\n\
  -s  saturation (0-254)\n\
  -f  profile (from config.h)\n\
  -r  register with bridge\n\
  -g  get some info about a light\n\
  -h  show this help\n");
}

int main(int argc, char *argv[])
{
  int opt;
  int light = DEFAULT_LIGHT;

  if (argc < 2) {
    printhelp();
    error("no argument provided");
  }

  // handle commandline arguments
  while ((opt = getopt(argc, argv, "hrgc:l:b:s:p:f:")) != -1) {
   switch (opt) {
   case 'l':
     light = atoi(optarg);
     break;
   case 'b':
     if (atoi(optarg) >= 0 && atoi(optarg) <= 254) {
       setProp("PUT", light, "state", "bri", optarg);
     }
     else {
       printhelp();
     }
     break;
   case 'r':
    printf("HUE BRIDGE RESPONSE:\n\n%s\n\n\nif registered successfully, wrote token to privconfig.h\n", registerWithBridge());
     break;
   case 's':
     if (atoi(optarg) >= 0 && atoi(optarg) <= 254) {
       setProp("PUT", light, "state", "sat", optarg);
     }
     else {
       printhelp();
     }
     break;
   case 'p':
     if (atoi(optarg) == 1) {
       setProp("PUT", light, "state", "on", "true");
     }
     else if (atoi(optarg) == 0) {
       setProp("PUT", light, "state", "on", "false");
     }
     else {
       printhelp();
     }
     break;
   case 'c':
     if (atoi(optarg) >= 0 && atoi(optarg) <= 65535) {
       setProp("PUT", light, "state", "hue", optarg);
     }
     else {
       printhelp();
     }
     break;
   case 'g':
		 char *apidata = sendRequest("GET", light, "", 1, "", "");
		 printf("is on: %s\n", regexMatch(regexMatch(apidata, "\"on\":[^,]*", 1), ":.*", 1)+1);
		 printf("brightness: %s\n", regexMatch(regexMatch(apidata, "\"bri\":[^,]*", 1), ":.*", 1)+1);
		 printf("hue: %s\n", regexMatch(regexMatch(apidata, "\"hue\":[^,]*", 1), ":.*", 1)+1);
		 printf("saturation: %s\n", regexMatch(regexMatch(apidata, "\"sat\":[^,]*", 1), ":.*", 1)+1);
		 printf("color temp (only white): %s\n", regexMatch(regexMatch(apidata, "\"ct\":[^,]*", 1), ":.*", 1)+1);
		 printf("\nname: %s\n", regexMatch(regexMatch(apidata, "\"name\":[^,]*", 1), ":\".*\"", 1)+1);
		 printf("type: %s\n", regexMatch(regexMatch(apidata, "\"type\":[^,]*", 1), ":.*", 1)+1);
		 printf("sw version: %s\n", regexMatch(regexMatch(apidata, "\"swversion\":[^,]*", 1), ":.*", 1)+1);
     break;
   case 'f':
     if (atoi(optarg) >= 0 && atoi(optarg) <= (int) (sizeof(profiles)/sizeof(profiles[0]) - 1)) {
       setProp("PUT", light, "state", "on", "true");
       for (int i = 0; i < 3; i++) {
         setProp("PUT", light, "state", profileorder[i], profiles[atoi(optarg)][i]);
       }
     } else {
       error("profile doesn't exist.");
     }
     break;
   default:
     printhelp();
   }
  }
  return 0;
}

#include <stdio.h>
#include <getopt.h>

#include "comms.h"

void printhelp()
{
  printf("cli options:\n\
  -l  light, if not provided use default\n\
  -p  1 (on) or 0 (off)\n\
  -b  brightness (0-254)\n\
  -c  hue (0-65535)\n\
  -s  saturation (0-254)\n\
  -f  profile (from config.h)\n\
  -r  register with bridge\n\
  -g  get a property from the api\n\
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
  while ((opt = getopt(argc, argv, "hrc:l:b:s:p:g:f:")) != -1) {
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
     if (argc > 3) {
       error("-g can only be used alone");
     }
     if (strlen(argv[2]) > 10) {
       printhelp();
     }
     else {
       printf("%s\n", getProp(light, optarg));
     }
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

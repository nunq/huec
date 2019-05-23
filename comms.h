#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <sys/types.h>

#include "tcphandler.h"
#include "privconfig.h"

char *sendRequest(const char *method, const int light, const char *action, const int nojson, const char *property, const char *state) {

  char *response;
  char httpbody[256];
  char req[MAXLINE];
  int contlen;

  if (nojson == 0) {
    snprintf(httpbody, sizeof(httpbody), "{\"%s\": %s}", property, state);
  }

  contlen = strlen(httpbody);

  createSocket();

  // request builder
  snprintf(req, sizeof(req), "%s /api/%s/lights/%d/%s HTTP/1.0\r\nContent-Length: %d\r\n\r\n%s\r\n", method, TOKEN, light, action, contlen, httpbody);

  if (strcmp((response = RequestHandler(req)), "") == 0) {
    return "sendRequest: response is empty";
  }
  else {
    return response;
  }
}


char *getProp(const int light, const char *property) {

  char *returned;
  char *source;
  char pattern[32]; //buffer
  int offset = 2;
  char *patternstr = "\\\"\\\":[^,]*";

  source = sendRequest("GET", light, "", 1, "", "");

  // insert property into pattern buffer
  strncpy(pattern, patternstr, offset);
  pattern[offset] = '\0';
  strcat(pattern, property);
  strcat(pattern, patternstr + offset);

  returned = regexMatch(source, pattern, 1);

  if (strcmp(returned, "no match") == 0) {
    return "regex match (1) failed";
  }

  returned = regexMatch(returned, ":.*", 1);

  if (strcmp(returned, "no match") == 0) {
    return "regex match (2) failed";
  }

  returned += 1;
  return returned;
}


int setProp(const char *method, const int light, const char *action, const char *property, const char *state) {

  char buffer[128];
  int retval;
  regex_t regex;

  char *source = sendRequest(method, light, action, 0, property, state);

  if ( (retval = regcomp(&regex, "success", 0) != 0)) {
    regerror(retval, &regex, buffer, sizeof(buffer));
    fprintf(stderr, "regcomp error: %s\n", buffer);
    exit(-1);
  }

  retval = regexec(&regex, source, 0, NULL, 0);

  if (retval == REG_NOMATCH) {
    return 1;
  }
  else {
    return 0;
  }
}

char *registerWithBridge() {
// runs on -r from cli.h
  char *response;
  char httpbody[256];
  char req[MAXLINE];
  int contlen;
// for un, use huec-epochtime or prnged number set before as var
  snprintf(httpbody, sizeof(httpbody), "{\"username\": \"huec demo\", \"devicetype\": \"huec demo device\"}");

  contlen = strlen(httpbody);

  createSocket();

  // request builder
  snprintf(req, sizeof(req), "POST /api HTTP/1.0\r\nContent-Length: %d\r\n\r\n%s\r\n", contlen, httpbody);

  if (strcmp((response = RequestHandler(req)), "") == 0) {
    return "sendRequest: response is empty";
  }
  else {
  //match for "success", if matched
  //fopen() put token in ./privconfig.h
    return "test";
  }
}

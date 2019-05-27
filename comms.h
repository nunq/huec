#include <stdio.h>

#include "tcphandler.h"
#include "privconfig.h"

char *sendRequest(const char *method, const int light, const char *action, const int nojson, const char *property, const char *state)
{
  char *response;
  char httpbody[256];
  char req[MAXLINE];
  int contlen;

  // decide if json data should be included in the request
  if (nojson == 0) {
    snprintf(httpbody, sizeof(httpbody), "{\"%s\": %s}", property, state);
  }

  contlen = strlen(httpbody);

  createSocket();

  // request builder
  snprintf(req, sizeof(req), "%s /api/%s/lights/%d/%s HTTP/1.0\r\nContent-Length: %d\r\n\r\n%s\r\n", method, TOKEN, light, action, contlen, httpbody);

  if (strcmp((response = RequestHandler(req)), "") == 0) {
    error("sendRequest(): response from bridge is empty");
  }
  else {
    return response;
  }
}

char *getProp(const int light, const char *property)
{
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

  // regex match target json data
  if (strcmp(returned, "no match") == 0) {
    return "regex match (1) failed";
  }

  returned = regexMatch(returned, ":.*", 1);

  if (strcmp(returned, "no match") == 0) {
    return "regex match (2) failed";
  }
  // remove colon from string
  returned += 1;
  return returned;
}

int setProp(const char *method, const int light, const char *action, const char *property, const char *state)
{
  char *source = sendRequest(method, light, action, 0, property, state);

  if (strcmp(regexMatch(source, "success", 0), "match found") == 0) {
    return 0;
  }
  else {
    return 1;
  }
}

char *registerWithBridge()
{
// runs on -r
  char *response;
  char httpbody[256];
  char req[MAXLINE];
  int contlen;
  char *filtertoken;

  snprintf(httpbody, sizeof(httpbody), "{\"devicetype\": \"huec-client#huec\"}");
  contlen = strlen(httpbody);

  createSocket();

  // request builder
  snprintf(req, sizeof(req), "POST /api HTTP/1.0\r\nContent-Length: %d\r\n\r\n%s\r\n", contlen, httpbody);

  if (strcmp((response = RequestHandler(req)), "") == 0) {
    error("registerWithBridge(): response from bridge is empty");
  }
  else {

    // regex match target json data
    filtertoken = regexMatch(response, "\"username\":\".*\"", 1);
    if (strcmp(filtertoken, "no match") == 0) {
      printf("%s\n", "regex match for token (1) failed");
    }

    filtertoken = regexMatch(filtertoken, ":.*", 1);
    if (strcmp(filtertoken, "no match") == 0) {
      printf("%s\n", "regex match for token (2) failed");
    }

    filtertoken += 1;

    // write token to privconfig.h
    FILE *fp = fopen(PRIVCONFIGPATH, "w");

    if (fp == NULL) {
      error("registerWithBridge(): fopen failed";
    }

    fprintf(fp, "#define TOKEN %s\n", filtertoken);
    fclose(fp);

    return response;
  }
}

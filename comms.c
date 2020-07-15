#include <stdio.h>
#include <string.h>

#include "privconfig.h"
#include "tcphandler.h"
#include "util.h"
#include "config.h"

char *sendRequest(const char *method, const int light, const char *action, const int nojson, const char *property, const char *state)
{
  char *response;
  char httpbody[256];
  char req[4096];
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
    return "err"; //isn't going to run, but makes gcc happy
  }
  else {
    return response;
  }
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
  char req[4096];
  int contlen;
  char *filtertoken;

  snprintf(httpbody, sizeof(httpbody), "{\"devicetype\": \"huec-client#huec\"}");
  contlen = strlen(httpbody);

  createSocket();

  // request builder
  snprintf(req, sizeof(req), "POST /api HTTP/1.0\r\nContent-Length: %d\r\n\r\n%s\r\n", contlen, httpbody);

  if (strcmp((response = RequestHandler(req)), "") == 0) {
    error("registerWithBridge(): response from bridge is empty");
    return "err"; //isn't going to run, but makes gcc happy
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
      error("registerWithBridge(): fopen failed");
      return "err"; //isn't going to run, but makes gcc happy
    }

    fprintf(fp, "#define TOKEN %s\n", filtertoken);
    fclose(fp);

    return response;
  }
}

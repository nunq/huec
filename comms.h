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
  char *clean;
  char *pattern;
  char *source;
  char buffer[128];
  char prematched[128];
  int retval;
  regex_t regex;
  regmatch_t pmatch[2];
  size_t nmatch = 2;
  static char matched[128];

  char firstpattern[32]; //buffer
  char *patternstr = "\\\"\\\":[^,]*";
  int offset = 2;

  source = sendRequest("GET", light, "", 1, "", "");

  strncpy(firstpattern, patternstr, offset);
  firstpattern[offset] = '\0';
  strcat(firstpattern, property);
  strcat(firstpattern, patternstr + offset);

  if ( (retval = regcomp(&regex, firstpattern, REG_EXTENDED) != 0)) {
    regerror(retval, &regex, buffer, sizeof(buffer));
    fprintf(stderr, "regcomp error: %s\n", buffer);
    exit(-1);
  }

  retval = regexec(&regex, source, nmatch, pmatch, REG_NOTBOL);

  if (retval == REG_NOMATCH) {
    return "no match";
  }

  snprintf(prematched, 128, "%.*s", pmatch[0].rm_eo - pmatch[0].rm_so, &source[pmatch[0].rm_so]);
  regfree(&regex);


  pattern = ":.*";

  if ( (retval = regcomp(&regex, pattern, REG_EXTENDED) != 0)) {
    regerror(retval, &regex, buffer, sizeof(buffer));
    fprintf(stderr, "regcomp error: %s\n", buffer);
    exit(-1);
  }

  retval = regexec(&regex, prematched, nmatch, pmatch, 0);

  if (retval == REG_NOMATCH) {
    return "no match";
  }

  snprintf(matched, 128, "%.*s", pmatch[0].rm_eo - pmatch[0].rm_so, &prematched[pmatch[0].rm_so]);
  regfree(&regex);

  clean = matched + 1;

  return clean;
}


int setProp(const char *method, const int light, const char *action, const char *property, const char *state) {

  char buffer[128];
  int retval;
  regex_t regex;

  char *source = sendRequest("PUT", 1, action, 0, property, state);

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

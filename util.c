#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

void error(const char *msg)
{
  fprintf(stderr, "ERROR: %s\n", msg);
  exit(-1);
}

// abstract the regex matching
char *regexMatch(const char *source, const char *pattern, const int returnMatched)
{
  char buffer[128];
  int retval;
  regex_t regex;
  regmatch_t pmatch[2];
  size_t nmatch = 2;
  static char matched[128];

  if ( (retval = regcomp(&regex, pattern, REG_EXTENDED) != 0)) {
    regerror(retval, &regex, buffer, sizeof(buffer));
    regfree(&regex);
    error("regexMatch(): regcomp failed");
  }

  retval = regexec(&regex, source, nmatch, pmatch, REG_NOTBOL);

  if (retval == REG_NOMATCH) {
    regfree(&regex);
    return "no match";
  }

  if (returnMatched == 1) {
    snprintf(matched, sizeof(matched), "%.*s", (int) pmatch[0].rm_eo - (int) pmatch[0].rm_so, &source[pmatch[0].rm_so]);
    regfree(&regex);
    return matched;
  }
  else {
    regfree(&regex);
    return "match found";
  }
}

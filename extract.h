#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <sys/types.h>
//use error(); from util.h
//before exit close(sockfdA); in main()
//and free();
//

char *getProp(const char *property, char *source) {
  char *clean;
  char *pattern;
  char buffer[128];
  char matched[128];
  char prematched[128];
  int retval;
  regex_t regex;
  regmatch_t pmatch[2];
  size_t nmatch = 2;
  
  char firstpattern[32]; //buffer
  char *patternstr = "\\\"\\\":[^,]*";
  int offset = 2;

  strncpy(firstpattern, patternstr, offset);
  firstpattern[offset] = '\0';
  strcat(firstpattern, property);
  strcat(firstpattern, patternstr + offset);

  //pattern = "\"on\":[^,]*";

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

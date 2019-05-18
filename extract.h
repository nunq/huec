#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <sys/types.h>
//use error(); from util.h
//before exit close(sockfdA); in main()
//and free();
//
char matched[128];

char *getProp(const char *property, char *source) {
  regex_t regex;
  regmatch_t pmatch[2];
  int retval;
  char buffer[128];
  char prematched[128];
  size_t nmatch = 2;
  char *pattern;
  
  /*char pattern[32];
  // "\"XX\"\:.*?,"
  int offset = 2;

  strncpy(pattern, patternstr, offset);
  pattern[offset] = '\0';
  strcat(pattern, property);
  strcat(pattern, patternstr + offset);*/

  pattern = "\"on\":[^,]*";

  if ( (retval = regcomp(&regex, pattern, REG_EXTENDED) != 0)) {
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

  return matched;
}

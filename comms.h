# pragma once

char *sendRequest(const char *method, const int light, const char *action, const int nojson, const char *property, const char *state);
char *getProp(const int light, const char *property);
int setProp(const char *method, const int light, const char *action, const char *property, const char *state);
char *registerWithBridge();


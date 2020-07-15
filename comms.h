# pragma once

char *sendRequest(const char *method, const int light, const char *action, const int nojson, const char *property, const char *state);
int setProp(const char *method, const int light, const char *action, const char *property, const char *state);
char *registerWithBridge();


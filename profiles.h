# pragma once

// hue, saturation, brightness as integer values, obviously within the bounds (see ./hue -h)
const char *profileorder[] = { "hue", "sat", "bri" };
// profiles as a 2d array
char *profiles[][4] = {
  { "8916", "85", "190" },
  { "7541", "207", "116" },
  { "10286", "32", "66" },
  { "56167", "209", "73" },
  { "57396", "245", "11"}
};

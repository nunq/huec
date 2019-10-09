/* huec config.h */
// hue bridge info
#define HUE_IP_ADDR "192.168.178.50"
#define HUE_PORT 80
//default light (hue lights start at 1)
#define DEFAULT_LIGHT 1
// hue, saturation, brightness as integer values, obviously within the bounds (see ./hue -h)
const char *profileorder[] = { "hue", "sat", "bri" };
// profiles as a 2d array
char *profiles[][4] = { { "10286", "32", "66" }, { "56167", "209", "73" }, { "64333", "230", "45" }, { "57396", "245", "11"}, { "45824", "254", "134" } };
// for fopen()

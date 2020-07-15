# huec
a c program to control your hue lights

## setup / install

1. put the ip of your hue bridge in config.h
2. run ```make first```
3. press the link button on the hue bridge
4. run ```./hue -r```
5. run ```make hue```

> registration works best, if the delay between step 3 and 4 is small.

after that, you can just run ```make``` if you want to recompile the program.
note: if you changed something in the config, you need to recompile for the changes to take effect.

## usage
```
cli options:
  -l  light, if not provided use default
  -p  1 (on) or 0 (off)
  -b  brightness (0-254)
  -c  hue (0-65535)
  -s  saturation (0-254)
  -f  profile (from config.h)
  -r  register with bridge
  -g  get a property from the api (on, sat, bri, hue, ?)
  -h  show this help
```
### profiles

profiles can be set in profiles.h using a 2d array

## other

license: GPLv3

# huec
a c program to control your hue lights

still a WIP

## setup / install

1. run ```make first```
2. press link button on hue bridge
3. run ```./hue -r```
4. run ```make```

> registration works best, if the delay between step 2 and 3 is small.

after that, you can just run ```make``` if you want to recompile the program.

## usage
```
cli options:
-l  light, if not provided use default
-p  1 (on) or 0 (off)
-b  brightness (0-254)
-c  hue (0-65535)
-s  saturation (0-254)
-r  register with bridge
-h  show this help
else: returns 0
```
## other

License: MIT License

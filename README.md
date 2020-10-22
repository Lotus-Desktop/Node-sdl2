# Node-SDL2

A Basic binding for SDL2 Library for NodeJS

There weren't any maintained libraries that were compatible with Node.js v. 14+, so I wrote my own to use for Daisy 

# Building

Not a difficult library to build:

1. ```$ git clone https://github.com/Lotus-Desktop/Node-sdl2```
2. ```$ cd Node-sdl2```
3. ```$ pnpm install```
4. ```$ pnpx cmake-js .```
5. ```$ node ./test/circle.js```

Steps 4 and 5 are optional, the `./build.sh` file exists to replace those steps.
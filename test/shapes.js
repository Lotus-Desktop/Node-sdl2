#!/bin/bash

const sdl = require('../index');

const width = 720,
    height = 360;

sdl.init(sdl.initFlags.Video);
sdl.createWindowAndRenderer(width, height, 128);
sdl.setRenderDrawColour(0, 0, 0, 0);
sdl.renderClear();
sdl.renderPresent();

const draw = function () {
    sdl.setRenderDrawColour(0xff, 0xff, 0xff, 0xff);
    sdl.renderClear();

    sdl.setRenderDrawColour(0xff, 0, 0, 0xff);

    sdl.pollEvent();
    
    for (let i = 0; i < width; i++)
        sdl.renderDrawPoint(i, height / 2);
    
    sdl.setRenderDrawColour(0, 0xff, 0, 0xff);
    sdl.renderDrawRect(10, 10, width - 20, height - 20);
    
    sdl.setRenderDrawColour(0, 0xff, 0xff, 0xff);
    sdl.renderFillRect(25, 25, 50, 50);

    sdl.renderPresent();

}

while (sdl.getEvent().type !== sdl.Events.Quit)
    draw();

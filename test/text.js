#!/bin/bash

const sdl = require('../index');

const width = 720,
    height = 360;

sdl.init(sdl.initFlags.Video);
sdl.createWindowAndRenderer(width, height, 128);
sdl.setRenderDrawColour(0, 0, 0, 0);
sdl.renderClear();
sdl.renderPresent();

const OpenSans = sdl.loadFont("/home/jcake/.fonts/open-sans/OpenSans-BoldItalic.ttf");
sdl.setFont(OpenSans, 24);

const draw = function () {
    sdl.setRenderDrawColour(0xff, 0xff, 0xff, 0xff);
    sdl.renderClear();

    sdl.setRenderDrawColour(0xff, 0xff, 0xff, 0xff);

    sdl.pollEvent();

    sdl.setFont(OpenSans, 24);
    
    sdl.drawText(0, 0, "Hello World");
    
    sdl.setFont(OpenSans, 64);
    
    sdl.setTextColour(0x22, 0x22, 0x22, 0xff);
    sdl.drawText(0, 50, "Hi World, but BIGGER!");

    sdl.renderPresent();

}

// while (sdl.getEvent().type !== sdl.Events.Quit)
//     draw();
const int = setInterval(function() {
    if (sdl.getEvent().type === sdl.Events.Quit)
        clearInterval(int);
    else
        draw();
}, 1000 / 60);

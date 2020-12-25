#!/bin/bash

const sdl = require('../index');

const width = 720,
    height = 360;

sdl.init(sdl.initFlags.Video);
sdl.createWindowAndRenderer(width, height, 128);
sdl.setRenderDrawColour(0, 0, 0, 0);
sdl.renderClear();
sdl.renderPresent();

const OpenSans = sdl.loadFont("/home/jcake/.fonts/open-sans/OpenSans-Regular.ttf");
sdl.setFont(OpenSans, 20);

const draw = function () {
    // sdl.setRenderDrawColour(0xff, 0xff, 0xff, 0xff);
    sdl.setRenderDrawColour(0x00, 0x00, 0x00, 0x00);
    sdl.renderClear();

    sdl.setRenderDrawColour(0xff, 0xff, 0xff, 0xff);
    sdl.setTextColour(0xff, 0xff, 0xff, 0xff);

    sdl.pollEvent();
    
   const size = sdl.measureText("Hello", OpenSans);
   sdl.drawText(0, 0, "Hello");
   sdl.drawText(size.w, 0, "Bye");

    sdl.renderPresent();

}

const int = setInterval(function() {
    if (sdl.getEvent().type === sdl.Events.Quit)
        clearInterval(int);
    else
        draw();
}, 1000 / 60);

#!/bin/bash

const sdl = require('../index');

const width = 720,
    height = 360;

sdl.init(sdl.initFlags.Video);
sdl.createWindowAndRenderer(width, height, 128);
sdl.setRenderDrawColour(0, 0, 0, 0);
sdl.renderClear();
sdl.renderPresent();

const Rasa = sdl.loadFont("/home/jcake/Code/Project/Lotus/lib/native/sdl2/fonts/Rasa-Light.ttf", 24);

const draw = function () {
    sdl.setRenderDrawColour(0, 0, 0, 0xff);
    sdl.renderClear();

    sdl.setRenderDrawColour(0xff, 0xff, 0xff, 0xff);

    sdl.pollEvent();
    
    sdl.drawText(0, 0, "Hello World");

    sdl.renderPresent();

}

while (sdl.getEvent().type !== sdl.Events.Quit)
    draw();

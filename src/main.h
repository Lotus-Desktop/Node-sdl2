#pragma once

#include <napi.h>
#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "text/sdlStbFont.h"

namespace sdl2 {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    Napi::Function mouseMove;
    Napi::Function mouseDown;
    Napi::Function mouseUp;
    Napi::Function keyDown;
    Napi::Function keyUp;
    Napi::Function windowEvent;

    sdl_stb_font_cache fc;
    
    void init(const Napi::CallbackInfo &info);
    void createWindowAndRenderer(const Napi::CallbackInfo &info);
    void setRenderDrawColour(const Napi::CallbackInfo &info);
    void renderClear(const Napi::CallbackInfo &info);
    void renderPresent(const Napi::CallbackInfo &info);
    void destroyRenderer(const Napi::CallbackInfo &info);
    void destroyWindow(const Napi::CallbackInfo &info);
    void quit(const Napi::CallbackInfo &info);
    void renderDrawPoint(const Napi::CallbackInfo &info);
    void renderDrawRect(const Napi::CallbackInfo &info);
    void renderFillRect(const Napi::CallbackInfo &info);
    void delay(const Napi::CallbackInfo &info);
    void pollEvent(const Napi::CallbackInfo &info);

    Napi::Object Init(Napi::Env env, Napi::Object exports);
    NODE_API_MODULE(addon, Init);
}

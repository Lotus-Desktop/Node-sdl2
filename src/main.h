#pragma once

#include <napi.h>
#include <SDL.h>
#include <iostream>

#include "text/sdlStbFont.h"

namespace sdl2 {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    sdl_stb_font_cache fc;
    
    Napi::Number init(const Napi::CallbackInfo &info);
    Napi::Number createWindowAndRenderer(const Napi::CallbackInfo &info);
    Napi::Number setRenderDrawColour(const Napi::CallbackInfo &info);
    Napi::Number renderClear(const Napi::CallbackInfo &info);
    void renderPresent(const Napi::CallbackInfo &info);
    void destroyRenderer(const Napi::CallbackInfo &info);
    void destroyWindow(const Napi::CallbackInfo &info);
    void quit(const Napi::CallbackInfo &info);
    Napi::Number renderDrawPoint(const Napi::CallbackInfo &info);
    void renderDrawRect(const Napi::CallbackInfo &info);
    void renderFillRect(const Napi::CallbackInfo &info);
    void delay(const Napi::CallbackInfo &info);
    Napi::Number pollEvent(const Napi::CallbackInfo &info);

    Napi::Object Init(Napi::Env env, Napi::Object exports);
    NODE_API_MODULE(addon, Init)
}

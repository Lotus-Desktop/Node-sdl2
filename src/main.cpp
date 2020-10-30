#include <iostream>
#include <stdio.h>

#include <SDL.h>

#include "main.h"
#include "util.h"
#include "extras.h"

#define SDL_STB_FONT_IMPL
#include "text/sdlStbFont.h"

Napi::Number sdl2::init(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1 || !info[0].IsNumber())
        Napi::TypeError::New(env, "Expected Number").ThrowAsJavaScriptException();

    Napi::Number flags = info[0].As<Napi::Number>();

    Napi::Number returnValue = Napi::Number::New(env, SDL_Init(flags.Uint32Value()));

    return returnValue;
}

Napi::Number sdl2::createWindowAndRenderer(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() != 3 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber())
        Napi::TypeError::New(env, "Expected Number").ThrowAsJavaScriptException();

    Napi::Number width = info[0].As<Napi::Number>();
    Napi::Number height = info[1].As<Napi::Number>();
    Napi::Number flags = info[2].As<Napi::Number>();

    Napi::Number returnValue = Napi::Number::New(env, SDL_CreateWindowAndRenderer(
                                                          width.Int64Value(),
                                                          height.Int64Value(),
                                                          flags.Uint32Value() | SDL_WINDOW_RESIZABLE,
                                                          &sdl2::window, &sdl2::renderer));

    return returnValue;
}

Napi::Number sdl2::setRenderDrawColour(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() != 4 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[2].IsNumber())
        Napi::TypeError::New(env, "Expected Number").ThrowAsJavaScriptException();

    Napi::Number r = info[0].As<Napi::Number>();
    Napi::Number g = info[1].As<Napi::Number>();
    Napi::Number b = info[2].As<Napi::Number>();
    Napi::Number a = info[3].As<Napi::Number>();

    Napi::Number returnValue = Napi::Number::New(env, SDL_SetRenderDrawColor(
                                                          sdl2::renderer,
                                                          (Uint8)r.Uint32Value(),
                                                          (Uint8)g.Uint32Value(),
                                                          (Uint8)b.Uint32Value(),
                                                          (Uint8)a.Uint32Value()));

    return returnValue;
}

Napi::Number sdl2::renderClear(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    Napi::Number returnValue = Napi::Number::New(env, SDL_RenderClear(sdl2::renderer));

    return returnValue;
}

void sdl2::renderPresent(const Napi::CallbackInfo &info) {
    SDL_RenderPresent(sdl2::renderer);
}

void sdl2::destroyRenderer(const Napi::CallbackInfo &info) {
    SDL_DestroyRenderer(sdl2::renderer);
}

void sdl2::destroyWindow(const Napi::CallbackInfo &info) {
    SDL_DestroyWindow(sdl2::window);
}

void sdl2::quit(const Napi::CallbackInfo &info) {
    SDL_Quit();
}

Napi::Number sdl2::renderDrawPoint(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() != 2 || !info[0].IsNumber() || !info[1].IsNumber())
        Napi::TypeError::New(env, "Expected Number").ThrowAsJavaScriptException();

    Napi::Number x = info[0].As<Napi::Number>();
    Napi::Number y = info[1].As<Napi::Number>();

    Napi::Number returnValue = Napi::Number::New(env, SDL_RenderDrawPoint(sdl2::renderer, x.Int64Value(), y.Int64Value()));

    return returnValue;
}

void sdl2::renderDrawRect(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if ((info.Length() != 4 && info.Length() != 5) || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsNumber())
        Napi::TypeError::New(env, "Expected Number").ThrowAsJavaScriptException();

    Napi::Number x = info[0].As<Napi::Number>();
    Napi::Number y = info[1].As<Napi::Number>();
    Napi::Number w = info[2].As<Napi::Number>();
    Napi::Number h = info[3].As<Napi::Number>();
    
    Napi::Number r = Napi::Number::New(env, 1);
    if (info.Length() == 5)
        r = info[4].As<Napi::Number>();
    
    for (int i = 0; i < r.Int64Value(); i++) {
        SDL_Rect rect;
        
        rect.x = x.Int64Value() + i;
        rect.y = y.Int64Value() + i;
        rect.w = w.Int64Value() - i * 2;
        rect.h = h.Int64Value() - i * 2;
            
        SDL_RenderDrawRect(sdl2::renderer, &rect);
    }
}

void sdl2::renderFillRect(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() != 4 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsNumber())
        Napi::TypeError::New(env, "Expected Number").ThrowAsJavaScriptException();

    Napi::Number x = info[0].As<Napi::Number>();
    Napi::Number y = info[1].As<Napi::Number>();
    Napi::Number w = info[2].As<Napi::Number>();
    Napi::Number h = info[3].As<Napi::Number>();
    
    SDL_Rect rect;
        
    rect.x = x.Int64Value();
    rect.y = y.Int64Value();
    rect.w = w.Int64Value();
    rect.h = h.Int64Value();
    
    SDL_RenderFillRect(sdl2::renderer, &rect);
}


void sdl2::delay(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() != 1 || !info[0].IsNumber())
        Napi::TypeError::New(env, "Expected Number").ThrowAsJavaScriptException();

    Napi::Number ms = info[0].As<Napi::Number>();

    SDL_Delay(ms.Uint32Value());
}

Napi::Number sdl2::pollEvent(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env(); 

    Napi::Number returnValue = Napi::Number::New(env, SDL_PollEvent(&sdl2::event));

    return returnValue;
}

Napi::Object extras::getEvent(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::Object eventObj = Napi::Object::New(env);

    eventObj.Set("type", Napi::Number::New(env, sdl2::event.type));

    return eventObj;
}

void extras::loadFont(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    
    if (info.Length() != 2 || !info[0].IsString() || !info[1].IsNumber())
        Napi::TypeError::New(env, "Expected String, Number").ThrowAsJavaScriptException();
    
    Napi::String fontFile = info[0].As<Napi::String>();
    Napi::Number faceSize = info[1].As<Napi::Number>();
    
    sdl_stb_memory rasaLight;
    util::readFileRaw_toMemory(fontFile.Utf8Value(), rasaLight);
    sdl2::fc.faceSize = faceSize.Int64Value();
    sdl2::fc.loadFontManaged(rasaLight);
    sdl2::fc.bindRenderer(sdl2::renderer);
}

void extras::drawText(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    if (info.Length() != 3 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsString())
        Napi::TypeError::New(env, "Expected Number, Number, String").ThrowAsJavaScriptException();

    Napi::Number x = info[0].As<Napi::Number>();
    Napi::Number y = info[1].As<Napi::Number>();
    Napi::String string = info[2].As<Napi::String>();
    
    sdl2::fc.drawText(x.Int64Value(), y.Int64Value(), string.Utf8Value());
}

Napi::Object sdl2::Init(Napi::Env env, Napi::Object exports) {

    exports.Set("init", Napi::Function::New(env, sdl2::init));
    exports.Set("createWindowAndRenderer", Napi::Function::New(env, sdl2::createWindowAndRenderer));
    exports.Set("setRenderDrawColour", Napi::Function::New(env, sdl2::setRenderDrawColour));
    exports.Set("renderClear", Napi::Function::New(env, sdl2::renderClear));
    exports.Set("renderPresent", Napi::Function::New(env, sdl2::renderPresent));
    exports.Set("destroyRenderer", Napi::Function::New(env, sdl2::destroyRenderer));
    exports.Set("destroyWindow", Napi::Function::New(env, sdl2::destroyWindow));
    exports.Set("quit", Napi::Function::New(env, sdl2::quit));
    exports.Set("renderDrawPoint", Napi::Function::New(env, sdl2::renderDrawPoint));
    exports.Set("renderDrawRect", Napi::Function::New(env, sdl2::renderDrawRect));
    exports.Set("renderFillRect", Napi::Function::New(env, sdl2::renderFillRect));
    exports.Set("delay", Napi::Function::New(env, sdl2::delay));
    exports.Set("pollEvent", Napi::Function::New(env, sdl2::pollEvent));

    exports.Set("getEvent", Napi::Function::New(env, extras::getEvent));
    
    exports.Set("loadFont", Napi::Function::New(env, extras::loadFont));
    exports.Set("drawText", Napi::Function::New(env, extras::drawText));

    Napi::Object events = Napi::Object::New(env);
    events.Set("Quit", Napi::Number::New(env, SDL_QUIT));
    exports.Set("Events", events);

    Napi::Object initFlags = Napi::Object::New(env);
    initFlags.Set("Timer", Napi::Number::New(env, 0x00000001));
    initFlags.Set("Audio", Napi::Number::New(env, 0x00000010));
    initFlags.Set("Video", Napi::Number::New(env, 0x00000020));
    initFlags.Set("Joystick", Napi::Number::New(env, 0x00000200));
    initFlags.Set("Haptic", Napi::Number::New(env, 0x00001000));
    initFlags.Set("GameController", Napi::Number::New(env, 0x00002000));
    initFlags.Set("Events", Napi::Number::New(env, 0x00004000));
    initFlags.Set("Sensor", Napi::Number::New(env, 0x00008000));
    initFlags.Set("NoParachute", Napi::Number::New(env, 0x00100000));
    initFlags.Set("Everything", Napi::Number::New(env, 0x0010F231));
    exports.Set("initFlags", initFlags);

    Napi::Object windowFlags = Napi::Object::New(env);
    windowFlags.Set("Fullscreen", Napi::Number::New(env, 0x00000001));
    windowFlags.Set("FullscreenDesktop", Napi::Number::New(env, 0x00000002));
    windowFlags.Set("Opengl", Napi::Number::New(env, 0x00000004));
    windowFlags.Set("Vulkan", Napi::Number::New(env, 0x00000008));
    windowFlags.Set("Shown", Napi::Number::New(env, 0x00000010));
    windowFlags.Set("Hidden", Napi::Number::New(env, 0x00000020));
    windowFlags.Set("Borderless", Napi::Number::New(env, 0x00000040));
    windowFlags.Set("Resizable", Napi::Number::New(env, 0x00000080));
    windowFlags.Set("Minimized", Napi::Number::New(env, 0x00000100));
    windowFlags.Set("Maximized", Napi::Number::New(env, 0x00000200));
    windowFlags.Set("InputDrabbed", Napi::Number::New(env, 0x00000400));
    windowFlags.Set("InputFocus", Napi::Number::New(env, 0x00001000));
    windowFlags.Set("MouseFocus", Napi::Number::New(env, 0x00000800));
    windowFlags.Set("Foreign", Napi::Number::New(env, 0x00002000));
    windowFlags.Set("AllowHighdpi", Napi::Number::New(env, 0x00004000));
    windowFlags.Set("MouseCapture", Napi::Number::New(env, 0x00008000));
    windowFlags.Set("AlwaysOnTop", Napi::Number::New(env, 0x00010000));
    windowFlags.Set("SkipTaskbar", Napi::Number::New(env, 0x00020000));
    windowFlags.Set("Utility", Napi::Number::New(env, 0x00040000));
    windowFlags.Set("Tooltip", Napi::Number::New(env, 0x00080000));
    windowFlags.Set("PopupMenu", Napi::Number::New(env, 0x10000000));
    exports.Set("windowFlags", windowFlags);

    return exports;
}

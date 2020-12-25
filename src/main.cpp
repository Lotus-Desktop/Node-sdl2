#include <SDL.h>

#include "main.h"
#include "util.h"
#include "extras.h"
#include <iostream>

#define SDL_STB_FONT_IMPL

#include "text/sdlStbFont.h"

void sdl2::init(const Napi::CallbackInfo &info) {
    if (info.Length() != 1 || !info[0].IsNumber())
        Napi::TypeError::New(info.Env(), "Expected Number").ThrowAsJavaScriptException();

    auto flags = info[0].As<Napi::Number>();

    SDL_Init(flags.Uint32Value());
}

void sdl2::createWindowAndRenderer(const Napi::CallbackInfo &info) {
    if (info.Length() != 3 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber())
        Napi::TypeError::New(info.Env(), "Expected Number").ThrowAsJavaScriptException();

    auto width = info[0].As<Napi::Number>();
    auto height = info[1].As<Napi::Number>();
    auto flags = info[2].As<Napi::Number>();

    SDL_CreateWindowAndRenderer(width.Int64Value(), height.Int64Value(), flags.Uint32Value()| SDL_WINDOW_RESIZABLE,
                                &sdl2::window, &sdl2::renderer);
}

void sdl2::setRenderDrawColour(const Napi::CallbackInfo &info) {
    if (info.Length() != 4 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[2].IsNumber())
        Napi::TypeError::New(info.Env(), "Expected Number").ThrowAsJavaScriptException();

    auto r = info[0].As<Napi::Number>();
    auto g = info[1].As<Napi::Number>();
    auto b = info[2].As<Napi::Number>();
    auto a = info[3].As<Napi::Number>();

    // std::cout << r.Uint32Value() << ';' << g.Uint32Value() << std::endl;

    SDL_SetRenderDrawColor(sdl2::renderer, (Uint8) r.Uint32Value(), (Uint8) g.Uint32Value(), (Uint8) b.Uint32Value(),
                           (Uint8) a.Uint32Value());
}

void sdl2::renderClear(const Napi::CallbackInfo &info) {
    SDL_RenderClear(sdl2::renderer);
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

void sdl2::renderDrawPoint(const Napi::CallbackInfo &info) {
    if (info.Length() != 2 || !info[0].IsNumber() || !info[1].IsNumber())
        Napi::TypeError::New(info.Env(), "Expected Number").ThrowAsJavaScriptException();

    SDL_RenderDrawPoint(sdl2::renderer,
                        info[0].As<Napi::Number>().Int64Value(),
                        info[1].As<Napi::Number>().Int64Value());
}

void sdl2::renderDrawRect(const Napi::CallbackInfo &info) {
    if ((info.Length() != 4 && info.Length() != 5) || !info[0].IsNumber() || !info[1].IsNumber() ||
        !info[2].IsNumber() || !info[3].IsNumber())
        Napi::TypeError::New(info.Env(), "Expected Number").ThrowAsJavaScriptException();

    int r = 1;

    if (info.Length() == 5)
        r = info[4].As<Napi::Number>().Int64Value();

    for (int i = 0; i < r; i++) { // Redraw with a given border thickness
        SDL_Rect rect;

        rect.x = (int) info[0].As<Napi::Number>().Int64Value() + i;
        rect.y = (int) info[1].As<Napi::Number>().Int64Value() + i;
        rect.w = (int) info[2].As<Napi::Number>().Int64Value() - i * 2;
        rect.h = (int) info[3].As<Napi::Number>().Int64Value() - i * 2;

        SDL_RenderDrawRect(sdl2::renderer, &rect);
    }
}

void sdl2::renderFillRect(const Napi::CallbackInfo &info) {
    if (info.Length() != 4 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsNumber())
        Napi::TypeError::New(info.Env(), "Expected Number").ThrowAsJavaScriptException();

    SDL_Rect rect;

    rect.x = info[0].As<Napi::Number>().Int64Value();
    rect.y = info[1].As<Napi::Number>().Int64Value();
    rect.w = info[2].As<Napi::Number>().Int64Value();
    rect.h = info[3].As<Napi::Number>().Int64Value();

    SDL_RenderFillRect(sdl2::renderer, &rect);
}


void sdl2::delay(const Napi::CallbackInfo &info) {
    if (info.Length() != 1 || !info[0].IsNumber())
        Napi::TypeError::New(info.Env(), "Expected Number").ThrowAsJavaScriptException();

    SDL_Delay(info[0].As<Napi::Number>().Uint32Value());
}

void sdl2::pollEvent(const Napi::CallbackInfo &info) {
    SDL_PollEvent(&sdl2::event);
    
    extras::handleEvent(info);
}

Napi::Number extras::getEvent(const Napi::CallbackInfo &info) {
//    Napi::Object event = Napi::Object::New(info.Env());
//
//    event.Set("type", Napi::Number::New(info.Env(), sdl2::event.type));

    return Napi::Number::New(info.Env(), sdl2::event.type);
    // return event;
}

Napi::Number extras::loadFont(const Napi::CallbackInfo &info) {
    if (info.Length() != 1 || !info[0].IsString())
        Napi::TypeError::New(info.Env(), "Expected String").ThrowAsJavaScriptException();

    sdl_stb_memory font;
    util::readFileRaw_toMemory(info[0].As<Napi::String>().Utf8Value(), font);
    sdl2::fc.loadFontManaged(font);
    sdl2::fc.bindRenderer(sdl2::renderer);

    extras::fonts.push_back(font);

    return Napi::Number::New(info.Env(), extras::fonts.size() - 1);
}

void extras::setTextColour(const Napi::CallbackInfo &info) {
    if (info.Length() != 4 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber() || !info[3].IsNumber())
        Napi::TypeError::New(info.Env(), "Expected Number, Number, Number, Number").ThrowAsJavaScriptException();

    extras::textColour[0] = info[0].As<Napi::Number>().Int64Value();
    extras::textColour[1] = info[1].As<Napi::Number>().Int64Value();
    extras::textColour[2] = info[2].As<Napi::Number>().Int64Value();
    extras::textColour[3] = info[3].As<Napi::Number>().Int64Value();
}

void extras::setFont(const Napi::CallbackInfo &info) {
    if (info.Length() != 2 || !info[0].IsNumber() || !info[1].IsNumber())
        Napi::TypeError::New(info.Env(), "Expected Number, Number").ThrowAsJavaScriptException();

    int fontId = info[0].As<Napi::Number>().Int64Value();

    if (extras::fonts.size() <= fontId)
        Napi::RangeError::New(info.Env(), "Unknown Font ID").ThrowAsJavaScriptException();

    sdl2::fc.clearGlyphs();
    sdl2::fc.faceSize = info[1].As<Napi::Number>().Int64Value();
    sdl2::fc.loadFontManaged(extras::fonts[fontId]);
}

void extras::drawText(const Napi::CallbackInfo &info) {
    if (info.Length() != 3 || !info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsString())
        Napi::TypeError::New(info.Env(), "Expected Number, Number, String").ThrowAsJavaScriptException();

    sdl_stb_prerendered_text prt;
    sdl2::fc.renderTextToObject(&prt, info[2].As<Napi::String>().Utf8Value());
    prt.drawWithColorMod(sdl2::renderer,
                         info[0].As<Napi::Number>().Int64Value(),
                         info[1].As<Napi::Number>().Int64Value(),
                         extras::textColour[0], extras::textColour[1],
                         extras::textColour[2], extras::textColour[3]);
    prt.freeTexture();
}

Napi::Object extras::measureText(const Napi::CallbackInfo &info) {
    if ((info.Length() == 2 && (!info[0].IsString() || !info[1].IsNumber())) ||
        (info.Length() == 1 && !info[0].IsString()))
        Napi::TypeError::New(info.Env(), "Expected String, Number?").ThrowAsJavaScriptException();

    std::string string = info[0].As<Napi::String>().Utf8Value();
    Napi::Object result = Napi::Object::New(info.Env());

    if (info[1].IsNumber()) {
        int fontId = info[1].As<Napi::Number>().Int64Value();

        sdl2::fc.clearGlyphs();
        sdl2::fc.loadFontManaged(extras::fonts[fontId]);
    }

    sdl_stb_formatted_text text;
    text << string;

    int w, h;
    sdl2::fc.getTextSize(w, h, text);

    result.Set("width", Napi::Number::New(info.Env(), w));
    result.Set("height", Napi::Number::New(info.Env(), h));

    return result;
}

void addListener(const Napi::CallbackInfo &info) {
    if (info.Length() != 2 || !info[0].IsString() || !info[1].IsFunction())
        Napi::TypeError::New(info.Env(), "Expected String, (data: any) => void").ThrowAsJavaScriptException();

    std::string eventHandler = info[0].As<Napi::String>().Utf8Value();

    if (eventHandler == "mouseMove")
        sdl2::mouseMove = info[1].As<Napi::Function>();
        // sdl2::mouseMove.push_back(callback);
    else if (eventHandler == "mouseDown")
        sdl2::mouseDown = info[1].As<Napi::Function>();
        // sdl2::mouseDown.push_back(callback);
    else if (eventHandler == "mouseUp")
        sdl2::mouseUp = info[1].As<Napi::Function>();
        // sdl2::mouseUp.push_back(callback);
    else if (eventHandler == "keyDown")
        sdl2::keyDown = info[1].As<Napi::Function>();
        // sdl2::keyDown.push_back(callback);
    else if (eventHandler == "keyUp")
        sdl2::keyUp = info[1].As<Napi::Function>();
        // sdl2::keyUp.push_back(callback);
    else if (eventHandler == "windowStateChange")
        sdl2::windowEvent = info[1].As<Napi::Function>();
        // sdl2::windowEvent.push_back(callback);
    else
        Napi::TypeError::New(info.Env(), "Unknown event " + eventHandler + ".").ThrowAsJavaScriptException();
}

Napi::Object extras::getMouse(const Napi::CallbackInfo &info) {
    Napi::Object mouse = Napi::Object::New(info.Env());

    int x, y;

    SDL_PumpEvents();
    SDL_GetMouseState(&x, &y);

    mouse.Set("x", Napi::Number::New(info.Env(), x));
    mouse.Set("y", Napi::Number::New(info.Env(), y));

    return mouse;
}

bool isWindowEvent(SDL_Event event) {
   if (event.type == SDL_WINDOWEVENT_RESIZED ||
       event.type == SDL_WINDOWEVENT_RESTORED ||
       event.type == SDL_WINDOWEVENT_MAXIMIZED ||
       event.type == SDL_WINDOWEVENT_MINIMIZED ||
       event.type == SDL_WINDOWEVENT_MOVED ||
       event.type == SDL_WINDOWEVENT_FOCUS_GAINED ||
       event.type == SDL_WINDOWEVENT_FOCUS_LOST ||
       event.type == SDL_WINDOWEVENT_SIZE_CHANGED)
       return true;
   else
       return false;
}

void extras::handleEvent(const Napi::CallbackInfo& info) { // This is not an exported function
    
    if (sdl2::event.type == SDL_MOUSEMOTION) {
        
//        int x, y;
//
//        SDL_PumpEvents();
//        SDL_GetMouseState(&x, &y);O

//        std::cout << "Calling handler" << std::endl;
//         sdl2::mouseMove.Call({});

    }
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

    exports.Set("getMouse", Napi::Function::New(env, extras::getMouse));

    extras::textColour[0] = 0;
    extras::textColour[1] = 0;
    extras::textColour[2] = 0;
    extras::textColour[3] = 0xff;

    exports.Set("loadFont", Napi::Function::New(env, extras::loadFont));
    exports.Set("drawText", Napi::Function::New(env, extras::drawText));
    exports.Set("measureText", Napi::Function::New(env, extras::measureText));
    exports.Set("setFont", Napi::Function::New(env, extras::setFont));
    exports.Set("setTextColour", Napi::Function::New(env, extras::setTextColour));

    Napi::Object events = Napi::Object::New(env);

    events.Set("Quit", Napi::Number::New(env, SDL_QUIT));
    events.Set("WindowMove", Napi::Number::New(env, SDL_WINDOWEVENT_MOVED));
    events.Set("WindowResize", Napi::Number::New(env, SDL_WINDOWEVENT_RESIZED));
    events.Set("WindowRestore", Napi::Number::New(env, SDL_WINDOWEVENT_RESTORED));
    events.Set("WindowMinimised", Napi::Number::New(env, SDL_WINDOWEVENT_MINIMIZED));
    events.Set("WindowMaximised", Napi::Number::New(env, SDL_WINDOWEVENT_MAXIMIZED));
    events.Set("KeyDown", Napi::Number::New(env, SDL_KEYDOWN));
    events.Set("KeyUp", Napi::Number::New(env, SDL_KEYUP));
    events.Set("MouseDown", Napi::Number::New(env, SDL_MOUSEBUTTONDOWN));
    events.Set("MouseUp", Napi::Number::New(env, SDL_MOUSEBUTTONUP));
    events.Set("MouseWheel", Napi::Number::New(env, SDL_MOUSEWHEEL));
    events.Set("MouseMove", Napi::Number::New(env, SDL_MOUSEMOTION));
    events.Set("TouchDown", Napi::Number::New(env, SDL_FINGERDOWN));
    events.Set("TouchUp", Napi::Number::New(env, SDL_FINGERUP));
    events.Set("TouchMove", Napi::Number::New(env, SDL_FINGERMOTION));
    exports.Set("Events", events);

    exports.Set("on", Napi::Function::New(env, addListener));

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

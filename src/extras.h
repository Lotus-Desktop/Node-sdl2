#pragma once

#include <napi.h>
#include <vector>

namespace extras {
    std::vector<sdl_stb_memory> fonts;
    int textColour[4];
    
    void drawText(const Napi::CallbackInfo &info);
    Napi::Object getEvent(const Napi::CallbackInfo &info);
    Napi::Number loadFont(const Napi::CallbackInfo &info);
    void setTextColour(const Napi::CallbackInfo &info);
    void setFont(const Napi::CallbackInfo &info);
}

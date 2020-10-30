#pragma once

#include <napi.h>
#include <vector>

namespace extras {    
    void drawText(const Napi::CallbackInfo &info);
    Napi::Object getEvent(const Napi::CallbackInfo &info);
    void loadFont(const Napi::CallbackInfo &info);
}

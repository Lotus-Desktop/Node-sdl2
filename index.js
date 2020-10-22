const sdl = require("./build/Release/sdl2.node");

module.exports = {
    ...sdl,

    // Init Flags

    initFlags: {
        Timer: 0x00000001,
        Audio: 0x00000010,
        Video: 0x00000020,
        Joystick: 0x00000200,
        Haptic: 0x00001000,
        GameController: 0x00002000,
        Events: 0x00004000,
        Sensor: 0x00008000,
        NoParachute: 0x00100000,
        Everything: 0x0010F231,
    },

    // Window Flags

    windowFlags: {
        Fullscreen: 0x00000001,
        FullscreenDesktop: 0x00000002,
        Opengl: 0x00000004,
        Vulkan: 0x00000008,
        Shown: 0x00000010,
        Hidden: 0x00000020,
        Borderless: 0x00000040,
        Resizable: 0x00000080,
        Minimized: 0x00000100,
        Maximized: 0x00000200,
        InputDrabbed: 0x00000400,
        InputFocus: 0x00001000,
        MouseFocus: 0x00000800,
        Foreign: 0x00002000,
        AllowHighdpi: 0x00004000,
        MouseCapture: 0x00008000,
        AlwaysOnTop: 0x00010000,
        SkipTaskbar: 0x00020000,
        Utility: 0x00040000,
        Tooltip: 0x00080000,
        PopupMenu: 0x10000000
    }
};
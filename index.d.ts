export type eventName = "mouseMove" | "mouseDown" | "mouseUp" | "keyDown" | "keyUp" | "windowStateChange";

export enum initFlags {
    Timer = 0x00000001,
    Audio = 0x00000010,
    Video = 0x00000020,
    Joystick = 0x00000200,
    Haptic = 0x00001000,
    GameController = 0x00002000,
    Events = 0x00004000,
    Sensor = 0x00008000,
    NoParachute = 0x00100000,
    Everything = 0x0010F231
}

export enum windowFlags {
    Fullscreen = 0x00000001,
    FullscreenDesktop = 0x00000002,
    Opengl = 0x00000004,
    Vulkan = 0x00000008,
    Shown = 0x00000010,
    Hidden = 0x00000020,
    Borderless = 0x00000040,
    Resizable = 0x00000080,
    Minimized = 0x00000100,
    Maximized = 0x00000200,
    InputDrabbed = 0x00000400,
    InputFocus = 0x00001000,
    MouseFocus = 0x00000800,
    Foreign = 0x00002000,
    AllowHighdpi = 0x00004000,
    MouseCapture = 0x00008000,
    AlwaysOnTop = 0x00010000,
    SkipTaskbar = 0x00020000,
    Utility = 0x00040000,
    Tooltip = 0x00080000,
    PopupMenu = 0x10000000,
}

export enum Events {
    Quit = 0x100,
    WindowMove = 4,
    WindowResize = 5,
    WindowRestore = 9,
    WindowMinimised = 7,
    WindowMaximised = 8,
    KeyDown = 768,
    KeyUp = 769,
    MouseDown = 1025,
    MouseUp = 1026,
    MouseWheel = 1027,
    TouchDown = 1792,
    TouchUp = 1793,
    TouchMove = 1794
}

export function init(flags: number): number;

export function createWindowAndRenderer(width: number, height: number, flags: number): number;

export function setRenderDrawColour(red: number, green: number, blue: number, alpha: number): number;

export function renderClear(): number;

export function renderPresent(): void;

export function destroyRenderer(): void;

export function destroyWindow(): void;

export function quit(): void;

export function renderDrawPoint(x: number, y: number): number;

export function renderDrawRect(x: number, y: number, w: number, h: number, r?: number): number;

export function renderFillRect(x: number, y: number, w: number, h: number): number;

export function delay(ms: number): void;

export function pollEvent(): number;

export function getEvent(): number;

export function loadFont(fontFile: string): number;

export function setFont(fontId: number, fontSize: number): void;

export function setTextColour(r: number, g: number, b: number, a: number): void;

export function drawText(x: number, y: number, string: string): void;

export function measureText(text: string, fontId?: number): {width: number, height: number};

export function getMouse(): {x: number, y: number};

export function on(event: eventName, callback: (data: any) => void): void;

-- This file covers definitions for lhk_core.dll

---@meta

local G = {}

---@alias lhk.Strokes 'press'|'release'|'mirror'

---@class lhk.KeyStroke
---@field vkCode integer Virtual keycode of the keystroke
---@field scanCode integer Keyboard scancode of the keystroke
---@field stroke lhk.Strokes Stroke of the keystroke (press / release)

G.KeyStroke = {}

---Create a new lhk.KeyStroke userdata
---@param vkCode integer? Virtual keycode of the keystroke
---@param scanCode integer? Keyboard scancode of the keystroke
---@param stroke lhk.Strokes Stroke of the keystroke (press / release)
---@return lhk.KeyStroke
function G.KeyStroke.new(vkCode, scanCode, stroke)
end

G.Layer = {}

---Create a new layer
---@return lhk.Layer
function G.Layer.new()
end

---@class lhk.Layer
local Layer = {}

---Register a Keyboard hook that runs `actions` when `keyInfo` matches the currently pressed key
---@param self lhk.Layer
---@param keyFilter table Consists of:
---{
---    `vkCode` (int): Matches the virtual keycode of the pressed key
---    `scanCode` (int): Matches the scancode of the pressed key
---    `stroke` ('press'|'release'): Matches the stroke of the pressed key
---    `autorepeated` (int): Matches whether the key was autorepeated
---    `modifiers` (int): A table of the state of each modifier key to be matched (LWIN, LMENU, LCONTROL, LSHIFT, RWIN, RMENU, RCONTROL, RSHIFT)
---}
---When an entry doesn't exist, the corresponding condition is ignored.
---@param actions function|table Can either be:
---* A function: Receives a lhk.KeyStroke of the current keystroke
---* A lhk.KeyStroke array: Each keystroke is sent by lhk
---@param flags table? Consists of:
---{
---    `block` (bool): Whether to block the original keystroke; default `true`
---    `blockAutorepeat` (bool): Whether to block the original autorepeated keystroke; default `block`
---}
function Layer.register(self, keyFilter, actions, flags)
end

G.layers = {}

---Sets an array of layers to be used by lhk
---@param layers table An array of layers
function G.layers.set(layers)
end

G.keyboard = {}

---Return the key state of a given `vkCode`
---@param vkCode integer Virtual keycode of the given key
---@return integer state1
---@return integer state2
function G.keyboard.getKeyState(vkCode)
end

---Start lhk; this function will not return until lhk.stop() is called (Usually from a keyboard hook)
function G.start()
end

---Stop lhk and continue running the script
function G.stop()
end

return G

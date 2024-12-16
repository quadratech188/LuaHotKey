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

---@class lhk.Filter
---@field vkCode integer? Matches the virtual keycode of keys
---@field scanCode integer? Matches the scancode of keys
---@field stroke 'press'|'release'? Matches the stroke of keys
---@field autorepeated boolean? Matches whether the key was autorepeated
---@field modifiers lhk.Modifiers? Matches the state of modifiers when the key was pressed

---@class lhk.Flags
---@field block boolean? Whether to block the original keystroke; default `true`
---@field blockAutorepeat boolean? Whether to block the original keystroke if it is autorepeated; default `block`

---Register a Keyboard hook that runs `actions` when `keyInfo` matches the currently pressed key
---@param self lhk.Layer
---@param keyFilter lhk.Filter
---@param actions function|table Can either be:
---* A function: Receives a lhk.KeyStroke of the current keystroke
---* A lhk.KeyStroke array: Each keystroke is sent by lhk
---@param flags lhk.Flags?
function Layer.register(self, keyFilter, actions, flags)
end

---Pass on a `keystroke` to the next layer.
---@param self lhk.Layer
---@param keyStroke lhk.KeyStroke
function Layer.yield(self, keyStroke)
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

G.Modifiers = {}
---Create a new lhk.Modifiers userdata
---@param modifiers table The table of modifier states. keys can be: LWin, LMenu, LCtrl, LShift, RWin, RMenu, RCtrl, RShift. Missing keys default to false.
---Example:
---lhk.Modifiers.new {
---    LWin = true,
---    LMenu = true
---}
---@return lhk.Modifiers
function G.Modifiers.new(modifiers)
end

---@class lhk.Modifiers
local Modifiers = {}


---Start lhk; this function will not return until lhk.stop() is called (Usually from a keyboard hook)
function G.start()
end

---Stop lhk and continue running the script
function G.stop()
end

return G

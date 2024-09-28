-- This file covers definitions for lhk_core.dll and core_wrapper.lua

---@meta

local G = {}

---@class lhk.KeyStroke
---@field vkCode integer Virtual keycode of the keystroke
---@field scanCode integer Keyboard scancode of the keystroke
---@field stroke lhk.KeyStroke.strokes Stroke of the keystroke (press / release)

G.KeyStroke = {}

---Create a new lhk.KeyStroke userdata
---@param vkCode integer? Virtual keycode of the keystroke
---@param scanCode integer? Keyboard scancode of the keystroke
---@param stroke lhk.KeyStroke.strokes Stroke of the keystroke (press / release)
---@return lhk.KeyStroke
function G.KeyStroke.new(vkCode, scanCode, stroke)
end

G.Layer = {}

---Create a new layer (Not activated by default)
---@param name string Name of the layer
---@return lhk.Layer
function G.Layer.new(name)
end

---Get a layer by name
---@param name string Name of the layer
---@return lhk.Layer?
function G.Layer.get(name)
end

---@class lhk.Layer
---@field name string Name of the layer
---@field enabled boolean Whether the layer is enabled
local Layer = {}

---Activate the layer
---@param self lhk.Layer
function Layer.activate(self)
end

---Deactivate the layer
---@param self lhk.Layer
function Layer.deactivate(self)
end

---Register a Keyboard hook that runs `actions` when `keyInfo` matches the currently pressed key
---@param self lhk.Layer
---@param keyFilter table Consists of:
---{
---    `vkCode`: Matches the virtual keycode of the pressed key
---    `scanCode`: Matches the scancode of the pressed key
---    `stroke`: Matches the stroke (press / release) of the pressed key
---    `autorepeated`: Matches whether the key was autorepeated
---    `modifiers`: A table of the state of each modifier key to be matched (LWIN, LMENU, LCONTROL, LSHIFT, RWIN, RMENU, RCONTROL, RSHIFT)
---}
---When an entry doesn't exist, the corresponding condition is ignored.
---@param actions function|table Can either be:
---* A function: Receives a lhk.KeyStroke of the current keystroke
---* A lhk.KeyStroke array: Each keystroke is sent by lhk
---@param flags table? Consists of:
---{
---    `block`: Whether to block the original keystroke; default `true`
---    `blockAutorepeat`: Whether to block the original autorepeated keystroke; default `block`
---}
function Layer.register(self, keyFilter, actions, flags)
end

G.keyboard = {}

---Return the key state of a given `vkCode`
---@param vkCode integer Virtual keycode of the given key
---@return integer state1
---@return integer state2
function G.keyboard.getKeyState(vkCode)
end

---Start lhk; this function will run indefinitely
function G.start()
end

return G

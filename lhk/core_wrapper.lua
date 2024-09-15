local G = require 'lhk_core'
local vkCode = require 'vkCode'

---@enum lhk.KeyStroke.strokes
G.KeyStroke.strokes = {
	press = false,
	release = true
}

---Create a new lhk.KeyStroke userdata
---@param vkCode integer Virtual keycode of the keystroke
---@param stroke lhk.KeyStroke.strokes Stroke of the keystroke (press / release)
---@return lhk.KeyStroke
function G.KeyStroke.fromVkCode(vkCode, stroke)
	return G.KeyStroke.new(vkCode, nil, stroke)
end

---Create a new lhk.KeyStroke userdata
---@param scanCode integer Virtual keycode of the keystroke
---@param stroke lhk.KeyStroke.strokes Stroke of the keystroke (press / release)
---@return lhk.KeyStroke
function G.KeyStroke.fromScanCode(scanCode, stroke)
	return G.KeyStroke.new(nil, scanCode, stroke)
end

return G

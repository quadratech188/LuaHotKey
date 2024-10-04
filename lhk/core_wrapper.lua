local lhk_core = require 'lhk_core'

local G = {}

G.start = lhk_core.start

G.KeyStroke = {}

G.KeyStroke.new = lhk_core.KeyStroke.new

---Create a new lhk.KeyStroke userdata
---@param vkCode integer Virtual keycode of the keystroke
---@param stroke lhk.Strokes Stroke of the keystroke (press / release)
---@return lhk.KeyStroke
function G.KeyStroke.fromVkCode(vkCode, stroke)
	return G.KeyStroke.new(vkCode, nil, stroke)
end

---Create a new lhk.KeyStroke userdata
---@param scanCode integer Scancode of the keystroke
---@param stroke lhk.Strokes Stroke of the keystroke (press / release)
---@return lhk.KeyStroke
function G.KeyStroke.fromScanCode(scanCode, stroke)
	return G.KeyStroke.new(nil, scanCode, stroke)
end

G.Layer = {}

G.Layer = lhk_core.Layer

G.keyboard = {}

return G

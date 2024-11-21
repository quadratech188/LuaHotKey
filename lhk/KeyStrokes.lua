local vkCodes = require 'vkCode'.vkCodes

local core_wrapper = require 'lhk.core_wrapper'

local G = {}

---Returns an array of KeyStrokes
---@param data table An array of {`mod': 'modifiers`, `key`: `key`}s
---`modifiers`: A string of modifiers (See [Send](https://www.autohotkey.com/docs/v2/lib/Send.htm))
---`key`: vkCode of the desired key
function G.fromAHK(data)
	local map = {

		['^'] = 'LCtrl',
		['+'] = 'LShift',
		['!'] = 'LMenu',
		['#'] = 'LWin'
	}

	local last_modifiers = {
		['LCtrl'] = false,
		['LShift'] = false,
		['LMenu'] = false,
		['LWin'] = false
	}

	table.insert(data, {mod = '', key = nil}) -- Adding this resets all modifier keys

	local keyStrokes = {}

	for _, pair in ipairs(data) do
		local ahk_modifiers = pair.mod
		local key = pair.key

		if ahk_modifiers == nil then
			ahk_modifiers = ''
		end

		local modifiers = {
			['LCtrl'] = false,
			['LShift'] = false,
			['LMenu'] = false,
			['LWin'] = false
		}

		for i = 1, #ahk_modifiers do
			local char = ahk_modifiers:sub(i, i)
			modifiers[ map[char] ] = true
		end

		for modifier, state in pairs(modifiers) do
			if state == true and last_modifiers[modifier] == false  then
				table.insert(keyStrokes, core_wrapper.KeyStroke.fromVkCode(vkCodes[modifier], core_wrapper.KeyStroke.strokes.press))
			end
			if state == false and last_modifiers[modifier] == true then
				table.insert(keyStrokes, core_wrapper.KeyStroke.fromVkCode(vkCodes[modifier], core_wrapper.KeyStroke.strokes.release))
			end
		end
		
		if key ~= nil then
			table.insert(keyStrokes, core_wrapper.KeyStroke.fromVkCode(key, core_wrapper.KeyStroke.strokes.press))
			table.insert(keyStrokes, core_wrapper.KeyStroke.fromVkCode(key, core_wrapper.KeyStroke.strokes.release))
		end

		last_modifiers = modifiers
	end

	return keyStrokes
end

return G

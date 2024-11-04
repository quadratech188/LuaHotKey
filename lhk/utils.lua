local core_wrapper = require 'lhk.core_wrapper'
local vkCode = require 'vkCode'

local G = {}

---Create a layer that maps each entry in `from` to each entry in `to`
---@param from table An array of valid vkCode keys
---@param to table An array of valid vkCode keys
---@return lhk.Layer keyMap The keymap layer
function G.createKeyMap(from, to)
	local layer = core_wrapper.Layer.new()

	if #from ~= #to then
		error('`from` and `to` have different lengths', 2)
	end

	for i = 1, #from do
		local fromKey = vkCode.toVkCode(from[i])
		local toKey = vkCode.toVkCode(to[i])

		if fromKey == toKey then
			goto continue
		end

		layer:register({
			vkCode = fromKey
		},
		{
			core_wrapper.KeyStroke.fromVkCode(toKey, 'mirror')
		})

	    ::continue::
	end

	return layer
end

return G

local core_wrapper = require 'lhk.core_wrapper'

local G = {}

---Return an array of tables of modifier key states extracted from `str`
---If '!' exists in the string, the function will create a table where LMENU is on, and another where RMENU is on (unless < or > exists before it)
---@param str string
---@return table filterArray An array of `lhk.Modifiers`.
function G.filterFromAHK(str)
	local map = {
		['#'] = 'Win',
		['!'] = 'Menu',
		['^'] = 'Ctrl',
		['+'] = 'Shift'
	}

	local tables = {
		{}
	}
	for i = 1, #str do
		local char = str:sub(i, i)

		if map[char] ~= nil then
			local new_tables = {}

			for _, modifiers in ipairs(tables) do
				if str:sub(i - 1, i - 1) ~= '<' then
					local new_modifiers = {}

					for index, value in pairs(modifiers) do
						new_modifiers[index] = value
					end

					new_modifiers['R' .. map[char]] = true
					table.insert(new_tables, core_wrapper.Modifiers.new(new_modifiers))
				end

				if str:sub(i - 1, i - 1) ~= '>' then
					local new_modifiers = {}

					for index, value in pairs(modifiers) do
						new_modifiers[index] = value
					end

					new_modifiers['L' .. map[char]] = true
					table.insert(new_tables, core_wrapper.Modifiers.new(new_modifiers))
				end
			end
			tables = new_tables
		end
	end

	return tables
end

return G

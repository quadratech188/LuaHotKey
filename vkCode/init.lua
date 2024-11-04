local vkCodes = require 'vkCode.vkCodes'

local G = {
	vkCodes = vkCodes
}

---Convert a string as seen in vkCode.vkCodes to its corresponding vkCode
---@param char string
---@return integer
function G.toVkCode(char)
	if vkCodes[char] == nil then
		error(('\'%s\' is not a valid vkCode'):format(char), 2)
	end
	return vkCodes[char]
end

return G

package = "luahotkey"
version = "dev-1"
source = {
   url = "git+https://github.com/quadratech188/LuaHotKey"
}
supported_platforms = {
	'windows', 'win32', 'cygwin'
}
dependencies = {
	'lhk_core >= 0.1',
	'lua >= 5.1'
}
description = {
   homepage = "https://github.com/quadratech188/LuaHotKey",
   license = "MIT"
}
build = {
   type = "builtin",
   modules = {
	   lhk = 'lhk/init.lua',
	   ['lhk.core_wrapper'] = 'lhk/core_wrapper.lua',
	   ['lhk.modifiers'] = 'lhk/modifiers.lua',
	   ['lhk.KeyStrokes'] = 'lhk/KeyStrokes.lua',
	   ['lhk.definitions.lhk_core'] = 'definitions/lhk_core.lua',

	   vkCode = 'vkCode/init.lua',
	   ['vkCode.vkCodes'] = 'vkCode/vkCodes.lua'
   }
}

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
	   lhk = 'init.lua'
   }
}

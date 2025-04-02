#pragma once
#include <string>
#include <lualib.h>


namespace conversion::proto
{
	std::int32_t convert(std::uintptr_t party, lua_State* L, std::string_view chunk_name, std::string_view bytecode);
}
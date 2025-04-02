#pragma once
#include <string>
#include <optional>

namespace execution
{
	std::optional<std::string> run_script(const std::string& script, const std::string& chunk_name);
}
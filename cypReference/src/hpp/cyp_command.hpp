#pragma once
#include "cyp_common.hpp"

namespace cyp
{
	namespace command
	{
		void SystemCmd(const std::string& commad);
		void PopenCmd(const std::string& command);
		std::string GetStrPopenCmd(const std::string& command);
	}
}
#pragma once
#include "cyp_common.hpp"

namespace cyp
{
	namespace command
	{
		void systemCmd(const std::string& commad);
		void popenCmd(const std::string& command);
		std::string getStrPopenCmd(const std::string& command);
	}
}
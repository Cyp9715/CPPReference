#pragma once
#include "cyp_common.hpp"
#include <vector>
#include <string>

namespace cyp
{
	namespace vector
	{
		// declaration of template
		template<typename T>
		bool isContain(const std::vector<T>& v_input, const T find);
	

		// implementation of template
		template<typename T>
		bool isContain(const std::vector<T>& v_input, const T find)
		{
			if (std::find(v_input.begin(), v_input.end(), find) != v_input.end())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
	};


}
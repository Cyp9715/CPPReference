#include "cyp_vector.hpp"

namespace cyp
{
	namespace vector
	{
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
	}
}
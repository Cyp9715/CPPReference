#pragma once
#include <string>
#include <vector>

namespace cypReference
{
	namespace string
	{
		static bool z_isAlphabet(const std::string& input_);
		static bool z_isContain(const std::string& original, const std::string comparison_);
		static void z_Change(std::string& input_, const std::string& find_, const std::string& change);
		static bool z_isNumber(const std::string& input_);
	};


	namespace vector
	{
		template<typename T>
		static bool z_isContain(const std::vector<T>& original, const T find_);
	};
};
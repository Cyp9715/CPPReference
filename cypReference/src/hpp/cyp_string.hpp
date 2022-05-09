#pragma once
#include "cyp_common.hpp"

namespace cyp
{
	namespace string
	{
		bool IsAlphabet(const std::string& str);
		bool IsContain(const std::string& original, const std::string& find);
		bool IsNumber(const std::string& str);

		void ToLower(std::string& str);
		void ToUpper(std::string& str);
		void ChangeStr(std::string& str, const std::string& find, const std::string& change);

		// ex) str = "hii miii namee ciiyiipii" -> "hi mi namee ciyipi"
		// It can be usefully used for csv and tsv purification.
		void RemoveContinuousChar(std::string& str, char target);
		std::string RemoveExtension(const std::string& fileName, bool removeMultiExtension = false);
	};
}
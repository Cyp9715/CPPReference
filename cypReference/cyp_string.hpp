#pragma once
#include "cyp_common.hpp"

namespace cyp
{
	namespace string
	{
		bool isAlphabet(const std::string& str);
		bool isContain(const std::string& original, const std::string& find);
		bool isNumber(const std::string& str);

		void toLower(std::string& str);
		void toUpper(std::string& str);
		void changeStr(std::string& str, const std::string& find, const std::string& change);

		// ex) str = "hii miii namee ciiyiipii" -> "hi mi namee ciyipi"
		// It can be usefully used for csv and tsv purification.
		void removeContinuousChar(std::string& str, char target);
		std::string removeExtension(const std::string& fileName, bool removeMultiExtension = false);
	};
}
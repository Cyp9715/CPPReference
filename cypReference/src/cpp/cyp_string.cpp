#include "cyp_common.hpp"
#include "cyp_string.hpp"

namespace cyp
{
	namespace string
	{
		bool isContain(const std::string& input, const std::string& find)
		{
			if (input.find(find) == std::string::npos)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		void changeStr(std::string& str, const std::string& find, const std::string& change)
		{
			size_t ui_num = str.find(find);

			while (true)
			{
				if (ui_num == std::string::npos)
				{
					return;
				}
				else
				{
					str.erase(ui_num, find.size());
					str.insert(ui_num, change);
				}
				ui_num = str.find(find, change.size());
			}
		}

		bool isAlphabet(const std::string& str)
		{
			for (size_t i = 0; i < str.size(); ++i)
			{
				if ((str[i] >= 97 && 122 >= str[i]) || (str[i] >= 65 && 90 >= str[i]))
				{
					continue;
				}
				else
				{
					return false;
				}
			}
			return true;
		}

		bool isNumber(const std::string& str)
		{
			return !str.empty() && std::find_if(str.begin(), str.end(),
				[](unsigned char c) { return !std::isdigit(c); }) == str.end();
		}

		void toLower(std::string& str)
		{
			std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
		}

		void toUpper(std::string& str)
		{
			std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::toupper(c); });
		}

		void removeContinuousChar(std::string& str, char target)
		{
			for (int i = 0; i < str.length() - 1; ++i)
			{
				if (str[i] == target && str[i + 1] == target)
				{
					str.erase(i, 1);
					--i;
				}
			}
		}

		std::string removeExtension(const std::string& fileName, bool removeMultiExtension)
		{
			std::string temp_ = fileName;
			auto point = temp_.find('.');

			if (point == std::string::npos)
			{
				return "cyp::string::removeExtension() no exist extension point '.'";
			}

			if (removeMultiExtension)
			{
				temp_.erase(point);
			}
			else
			{
				auto rpoint = temp_.rfind('.');
				temp_.erase(rpoint);
			}

			return temp_;
		}

	}
}
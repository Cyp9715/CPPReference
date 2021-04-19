#include "cypCppReference.h"

bool cypReference::string::z_isContain(const std::string& input_, const std::string find_)
{
	if (input_.find(find_) == std::string::npos)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void cypReference::string::z_Change(std::string& input_, const std::string& find_, const std::string& change)
{
	size_t ui_num = input_.find(find_);

	while (true)
	{
		if (ui_num == std::string::npos)
		{
			return;
		}
		else
		{
			input_.erase(ui_num, find_.size());
			input_.insert(ui_num, change);
		}
		ui_num = input_.find(find_, change.size());
	}
}

bool cypReference::string::z_isAlphabet(const std::string& input_)
{
	for (size_t i = 0; i < input_.size(); ++i)
	{
		if ((input_[i] >= 97 && 122 >= input_[i]) || (input_[i] >= 65 && 90 >= input_[i]))
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

bool cypReference::string::z_isNumber(const std::string& input_)
{
	return !input_.empty() && std::find_if(input_.begin(), input_.end(), 
		[](unsigned char c) { return !std::isdigit(c); }) == input_.end();
}



template<typename T>
bool cypReference::vector::z_isContain(const std::vector<T>& v_input, const T find_)
{
	if (std::find(v_input.begin(), v_input.end(), find_) != v_input.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}


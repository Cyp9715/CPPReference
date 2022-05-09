#pragma once

#include <Windows.h>

namespace cyp
{
	namespace hook
	{
		class Hook_KeyBoard
		{
		private:

		public:
			void SetHook();
			void RemoveHook();
		};

		class Hook_Mouse
		{
		private:

		public:
		};
	}
}
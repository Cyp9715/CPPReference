#pragma once

#include "cyp_common.hpp"
#include <Windows.h>

namespace cyp
{
	namespace hook
	{
		class Hook_KeyBoard
		{
			static bool existHook;	// Prevent duplicate hooks created.
			static HHOOK _hook;
			static KBDLLHOOKSTRUCT _kbdStruct;

		private:
			LRESULT static __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam);
			SHORT static PRESSING_CONTROL();
			SHORT static PRESSING_SHIFT();

		public:
			bool SetHook();
			void RemoveHook();
		};

		class Hook_Mouse
		{
		private:

		public:

		};


	}
}
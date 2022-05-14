#pragma once

#include "cyp_common.hpp"
#include <Windows.h>

namespace cyp
{
	namespace hook
	{
		class Hook_KeyBoard
		{
			static bool _kbdExistHook;	// Prevent duplicate hooks created.
			static HHOOK _kbdHook;
			static KBDLLHOOKSTRUCT _kbdStruct;

		private:
			LRESULT static __stdcall HookCallback_KeyBoard(int nCode, WPARAM wParam, LPARAM lParam);
			SHORT static PRESSING_CONTROL();
			SHORT static PRESSING_SHIFT();
			SHORT static PRESSING_ALT();

		public:
			bool InstallHook();
			void UnInstallHook();
		};

		class Hook_Mouse
		{
			static bool _mslExistHook;	// Prevent duplicate hooks created.
			static HHOOK _mslHook;
			static MSLLHOOKSTRUCT _mslStruct;

		private:			
			LRESULT static __stdcall HookCallback_Mouse(int nCode, WPARAM wParam, LPARAM lParam);

		public:
			bool InstallHook();
			void UnInstallHook();
		};


	}
}
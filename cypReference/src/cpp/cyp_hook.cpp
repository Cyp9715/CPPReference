#include "cyp_hook.hpp"

namespace cyp
{
	namespace hook
	{ 
		HHOOK _hook;
		KBDLLHOOKSTRUCT _kbdStruct;

		LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
		{
			if (nCode >= 0)
			{
				if (wParam == WM_KEYDOWN)
				{
					_kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

					if (GetAsyncKeyState(VK_CONTROL) & 0x8000 && _kbdStruct.vkCode == VK_F2)
					{
						MessageBox(NULL, "Ctrl + F2 is pressed!", "key pressed", MB_ICONINFORMATION);
					}
				}

			}

			return CallNextHookEx(_hook, nCode, wParam, lParam);
		}

		void Hook_KeyBoard::SetHook()
		{
			if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
			{
				MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
			}
		}

		void Hook_KeyBoard::RemoveHook()
		{
			UnhookWindowsHookEx(_hook);
		}
	}
}

#include "cyp_hook.hpp"

namespace cyp
{
	namespace hook
	{
		HHOOK cyp::hook::Hook_KeyBoard::_hook;
		KBDLLHOOKSTRUCT cyp::hook::Hook_KeyBoard::_kbdStruct;
		bool cyp::hook::Hook_KeyBoard::existHook;
		
		LRESULT __stdcall Hook_KeyBoard::HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
		{
			if (nCode >= 0)
			{
				if (wParam == WM_KEYDOWN)
				{
					_kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

					switch (_kbdStruct.vkCode)
					{
					case VK_F2:
					{
						if (!PRESSING_CONTROL())
							goto nextHook;
						
						MessageBox(NULL, "Ctrl + F2 is pressed!", "key pressed", MB_ICONINFORMATION);
						break;
					}

					case VK_F1:
					{
						MessageBox(NULL, "F1 is pressed!", "key pressed", MB_ICONINFORMATION);
					}
					}
				}
			}

			nextHook:

			return CallNextHookEx(_hook, nCode, wParam, lParam);
		}

		SHORT Hook_KeyBoard::PRESSING_CONTROL()
		{
			return GetAsyncKeyState(VK_CONTROL) & 0x8000;
		}

		SHORT Hook_KeyBoard::PRESSING_SHIFT()
		{
			return GetAsyncKeyState(VK_SHIFT) & 0x8000;
		}

		bool Hook_KeyBoard::SetHook()
		{
			if (existHook == true) 
				return false;

			_hook = SetWindowsHookEx(WH_KEYBOARD_LL, Hook_KeyBoard::HookCallback, NULL, 0);

			if (_hook == NULL)
				return false;

			existHook = true;
			return true;
		}

		void Hook_KeyBoard::RemoveHook()
		{
			existHook = false;
			UnhookWindowsHookEx(_hook);
		}
	}
}

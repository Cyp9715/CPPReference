#include "cyp_hook.hpp"

namespace cyp
{
	namespace hook
	{
		// KeyBoard Hook

		HHOOK cyp::hook::Hook_KeyBoard::_kbdHook;
		KBDLLHOOKSTRUCT cyp::hook::Hook_KeyBoard::_kbdStruct;
		bool cyp::hook::Hook_KeyBoard::_kbdExistHook;
		
		LRESULT __stdcall Hook_KeyBoard::HookCallback_KeyBoard(int nCode, WPARAM wParam, LPARAM lParam)
		{
			if (nCode >= 0)
			{
				if (wParam == WM_KEYDOWN)
				{
					_kbdStruct = *(KBDLLHOOKSTRUCT*)lParam;

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

			return CallNextHookEx(_kbdHook, nCode, wParam, lParam);
		}

		SHORT Hook_KeyBoard::PRESSING_CONTROL()
		{
			return GetAsyncKeyState(VK_CONTROL) & 0x8000;
		}

		SHORT Hook_KeyBoard::PRESSING_SHIFT()
		{
			return GetAsyncKeyState(VK_SHIFT) & 0x8000;
		}

		SHORT Hook_KeyBoard::PRESSING_ALT()
		{
			return GetAsyncKeyState(VK_MENU) & 0x8000;
		}

		bool Hook_KeyBoard::InstallHook()
		{
			if (_kbdExistHook == true) 
				return false;

			_kbdHook = SetWindowsHookEx(WH_KEYBOARD_LL, Hook_KeyBoard::HookCallback_KeyBoard, NULL, 0);

			if (_kbdHook == NULL)
				return false;

			_kbdExistHook = true;
			return true;
		}

		void Hook_KeyBoard::UnInstallHook()
		{
			_kbdExistHook = false;
			UnhookWindowsHookEx(_kbdHook);
		}



		// Mouse Hook

		HHOOK cyp::hook::Hook_Mouse::_mslHook;
		MSLLHOOKSTRUCT cyp::hook::Hook_Mouse::_mslStruct;
		bool cyp::hook::Hook_Mouse::_mslExistHook;

		LRESULT __stdcall Hook_Mouse::HookCallback_Mouse(int nCode, WPARAM wParam, LPARAM lParam)
		{
			if (nCode >= 0)
			{
				_mslStruct = *(MSLLHOOKSTRUCT*)lParam;

				switch (wParam)
				{
				case WM_LBUTTONDOWN:
					MessageBox(NULL, "Mouse left button is pressed", "key pressed", MB_ICONINFORMATION);
					break;
				
				case WM_RBUTTONDOWN:
					MessageBox(NULL, "Mouse right button is pressed", "key pressed", MB_ICONINFORMATION);
					break;
				}
			}

			return CallNextHookEx(_mslHook, nCode, wParam, lParam);
		}

		bool Hook_Mouse::InstallHook()
		{
			if (_mslExistHook == true)
				return false;

			_mslHook = SetWindowsHookEx(WH_MOUSE_LL, HookCallback_Mouse, NULL, 0);

			if (_mslHook == NULL)
				return false;

			_mslExistHook = true;
			return true;
		}

		void Hook_Mouse::UnInstallHook()
		{
			_mslExistHook = false;
			UnhookWindowsHookEx(_mslHook);
		}
	}
}

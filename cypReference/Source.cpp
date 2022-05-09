#include <iostream>
#include <cyp_hook.hpp>

int main()
{
	cyp::hook::Hook_KeyBoard hook_keyBoard;
	hook_keyBoard.SetHook();
	hook_keyBoard.SetHook();

	cyp::hook::Hook_KeyBoard hook_keyBoard2;
	hook_keyBoard2.SetHook();



	MSG msg;

	while (GetMessage(&msg, 0, 0, 0))
	{

	};
}
#include <iostream>
#include "cypCppReference.h"

int main()
{
	cyp::communication::tcp *tcp = new cyp::communication::tcp();
	tcp->openClient("192.168.100.32",7777);
	tcp->sendClientToServer("123123");

	std::cout << tcp->clientReceive();
}

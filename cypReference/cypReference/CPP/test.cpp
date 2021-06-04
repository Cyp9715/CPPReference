#include <iostream>
#include "cypCppReference.h"

int main()
{
	std::filesystem::path example{ "ddd" };
	cyp::communication::tcp* tcp = new cyp::communication::tcp();
	tcp->openServer(7777);
	std::cout << tcp->receive();
	tcp->sendM();
}

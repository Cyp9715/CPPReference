#include <iostream>
#include "cypCppReference.h"

int main()
{
	cyp::communication::udp *udp = new cyp::communication::udp();
	udp->open("192.168.100.32", 7777);
	std::cout << udp->receive();
}

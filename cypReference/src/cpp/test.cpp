#include "cyp_communication.hpp"

int main()
{
	cyp::communication::Udp udp;
	udp.open_send("192.168.100.32", 5555);
	udp.open_receive(5555);
	udp.send("kimoukja");
	std::cout << udp.receive();

	//cyp::communication::Udp_multicast udp;
	//udp.send_open("224.100.100.99", 3001);
 //   udp.send("12555");
	//

	//udp.open_receive("224.100.100.99", 3001);
	//std::cout <<  udp.receive() << std::endl;
}
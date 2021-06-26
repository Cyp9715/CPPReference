#include "cypCppReference.h"

int main() 
{
	cyp::hash::SHA sha;
	cyp::hash::MD md;

	std::cout << md.strToMD5("C:\\Users\\Cyp\\Desktop\\openCV_고기동.cs");

	std::string a = "hii miii namee ciiyiipii";
	cyp::string::removeContinuousChar(a, 'i');
	std::cout << a << std::endl;
}
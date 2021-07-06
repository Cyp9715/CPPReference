# include "cyp_hash.hpp"

int main() 
{
	cyp::hash::SHA sha;
	sha.fileToSHA2_256("123");
}
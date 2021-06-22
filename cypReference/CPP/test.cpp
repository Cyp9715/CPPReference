#include "cypCppReference.h"
#include <iostream>
#include "cryptopp/sha.h"

int main()
{
	std::cout << cyp::string::removeExtension("asd.sd.kk", true);

    using namespace CryptoPP;

    SHA256 hash;
    std::cout << "Name: " << hash.AlgorithmName() << std::endl;
    std::cout << "Digest size: " << hash.DigestSize() << std::endl;
    std::cout << "Block size: " << hash.BlockSize() << std::endl;

    return 0;
}

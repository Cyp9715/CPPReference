# Cpp Reference

C++ libraries are complex, fragmented, and hard to find well abstracted libraries.

my personal reference is easy to use.(especially useful for beginner)

any comments on the source code are welcome.


# 1. License

<p align="center">
    <img src="https://i.imgur.com/GklIXU7.png"  width="560" height="362.25"/></center>
</p>

<h3 align="center">MIT LICENSE</h1>

However, additional library is included.

please check the libraries below, as they are licensed individually.

- [Cryptopp 8.6.0](https://github.com/weidai11/cryptopp) : Boost License
- [OpenCV 4.6.0](https://opencv.org/license/) : Apache 2

I am currently planning to change the encryption library to OpenSSL in relation to '''FIPS 140''' compliance.

After changing related Hash and Encrypte functions to OpenSSL

I plan to add a file encryption TCP transmission function using OpenSSL as well.


# 2. Environment


OS : Windows 10 and 11

Complier : Visual Studio 2022 / C++20 / x64 / MTd


I prefer to use the latest version.

whenever official versions of Windows OS, C++, Visual Studio, etc. are updated,

I will check the compatibility and update repositories

※ there are currently no plans to write Linux code.

# 3. Introduce namespaces
## 3-1. CypReference
include a lot of miscellaneous code.

- cyp::command
    + provide Windows command usage.
    + provide a function that return the result of command execution. 

- cyp::network
    + provide Tcp example
    + provide Udp example
    + provide Udp multicast example

- cyp::encrypt
    + provide AES encryption.
    + *except for AES 256, is not yet implemented properly...*
 
- cyp::file
    + create, delete, read, for files and folder
    + provide file transfer function (not encrypted).

- cyp::hardware
    + get monitors information (name, resolution, refresh rate, monitor position(x,y))

- cyp::hash

     use the hash function below for files and std::string.
    + MD5
    + SHA(SHA1, SHA2, SHA3)
     
     use the hash function below for std::string
    + PBKDF2
    + HKDF
   
- cyp::image
    + At the moment, have a code that can capture images simply (BMP, PNG). (will be changed to use OpenCV code in the future.)

- cyp::string
    + makes the std::string easier to use.
    
- cyp::timer
    + provide Timer
    + provide FpsCounter
    + run the callback function by attaching it to the timer (delay execution is possible)
 
- cyp::sharedMemory
    + provide shared memory(shared memory allows data to be shared between processes.)

- cyp:hook
    + provide Keyboard global hook. (need user implement)
    + provide Mouse global hook. (need user implement)

## 3-2. cypOpencvReference
*OpenCV related codes will be inserted.*

\* OpenCV version: 4.6.0

    

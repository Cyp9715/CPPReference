# Cpp Reference

C++ libraries are complex, fragmented, and hard to find well abstracted libraries.

my personal reference is easy to use.(especially useful for beginner)

any comments on the source code are welcome.


# 1. License

<p align="center">
    <img src="https://i.imgur.com/GklIXU7.png"  width="700" height="362.25"/></center>
</p>

<h3 align="center">MIT LICENSE</h1>

However, additional library is included.

Please check the libraries below, as they are licensed individually.

- [Cryptopp 8.6.0](https://github.com/weidai11/cryptopp) : Boost License

# 2. Environment


OS : Windows 10 and 11

Complier : Visual Studio 2022 / C++20 / x64 / MTd


I prefer to use the latest version.

whenever official versions of Windows OS, C++, Visual Studio, etc. are updated,

I will check the compatibility and update repositories

※ there are currently no plans to write Linux code.

# 3. Introduce namespaces
- cyp::command
    + use the Windows command.
    + get command return string.
 
- cyp::communication
    + use Tcp
    + use Udp
    + use Udp multicast.

- cyp::encrypt
    + You can use AES encryption.
    + *except for AES 256, is not yet implemented properly...*
 
- cyp::file
    + You can create, delete, read, for files and folder.
    + *planning to provide a class that transfers files through TCP.*

- cyp::hardware
    + You can get monitors information (name, resolution, refresh rate, monitor position(x,y))

- cyp::hash

     You can use the hash function below for files and std::string.
    + MD5
    + SHA
     
     You can use the hash function below for std::string
    + PBKDF2
    + HKDF
   
- cyp::image
    + At the moment, have a code that can capture images simply (BMP, PNG).
    + *decided to support OpenCV in the future.*

- cyp::string
    + makes the std::string easier to use.
    
- cyp::timer
    + use Timer
    + use FpsCounter
    + run the callback function by attaching it to the timer (delay execution is possible)
 
- cyp::sharedMemory
    + use shared memory(shared memory allows data to be shared between processes.)

- cyp:hook
    + use Keyboard global hook. (need implement)
    + use Mouse global hook. (need implement)

# 4. Caution
   Avoid using dynamic libraries.

   The lib folder contains dynamic library folders, but will not contain any files.

   I deliberately avoid using dll for stability.
    
   This code has no binary purpose, is to be built by implanting it into another code.
    

   Therefore, using dynamic libraries faced a number of miscellaneous problems,
    
   use dynamic libraries only for the purpose of distributing programs.

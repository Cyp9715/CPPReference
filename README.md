# Cpp Reference

C++ libraries are complex, fragmented, and hard to find well abstracted libraries.

my personal library is easy to use.(especially useful for beginner)

any comments on the source code are welcome.


# 1. License

![WTFPL](https://i.imgur.com/GklIXU7.png) 

<h3 align="center">MIT LICENSE</h1>

However, additional libraries have been installed.

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
    + You can use the Windows command. Using commands and receiving command return values are concisely configured.
- cyp::communication
    + You can use Tcp
    + You can use Udp
    + You can use Udp multicast.
- cyp::encrypt
    + You can use AES encryption.
    + *except for AES 256, is not yet implemented properly...*
- cyp::file
    + You can create, delete, read, for files and folder.
    + *planning to provide a class that transfers files through TCP.*
- cyp::hash

     You can use the hash function below for files and std::string.
    + MD5
    + SHA5
     
     You can use the hash function below for std::string
    + PBKDF2
    + HKDF
- cyp::string
    + makes the std::string easier to use.
- cyp::timer
    + You can use Timer
    + You can use FpsCounter
    + You can run the callback function by attaching it to the timer (delay execution is possible)
- cyp::sharedMemory
    + shared memory allows data to be shared between processes.
- cyp::image
    + At the moment, have a code that can capture images simply (BMP, PNG).
    + *Considering openCV support.*
- cyp:hook
    + *Not yet made (will support keyboard, mouse global hook).*
# 4. Caution

this code was created without thinking of continuous calls.

for this reason, some functions require modifications when used for the following purposes.

1. When analyzing large amounts of data.
 
※ Avoid using dynamic libraries.

   The lib folder contains dynamic library folders, but will not contain any files.

   I deliberately avoid using dll for stability.
    
   This code has no binary purpose, is to be built by implanting it into another code.
    

   Therefore, using dynamic libraries faced a number of miscellaneous problems,
    
   use dynamic libraries only for the purpose of distributing programs.

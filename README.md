# Cpp Reference

C++ libraries are complex, fragmented, and hard to find well abstracted libraries.

my personal library is easy to use.(especially useful for beginner)

any comments on the source code are welcome.


# 1. License

![WTFPL](https://i.imgur.com/nAsQFRo.png) 

<h3 align="center">DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE</h1>

However, additional libraries have been installed.

Please check the libraries below, as they are licensed individually.

- [Cryptopp 8.6.0](https://github.com/weidai11/cryptopp)

# 2. Environment


OS : Windows 10

Complier : C++20 / x64

Visual Studio : 2019 / MTd


I prefer to use the latest version.

whenever official versions of Windows OS, C++, Visual Studio, etc. are updated,

I will check the compatibility and update repositories

# 3. Introduce namespaces
- cyp::command
    + You can use the command. Using commands and receiving command return values are concisely configured.
- cyp::communication
    + You can use Tcp, Udp communication.
- cyp::encrypt
    + *It's not implemented properly yet.*
- cyp::file
    + You can Create, delete, read, for files and folder.
- cyp::hash
    + You can create sha, md5 hash values for std::string and files.
- cyp::string
    + You can std::string is more comfortable.
- cyp::timer
    + You can use Timer and FpsCounter.
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

    The cyp::vector::isContain() = has a time complexity of O(n). This is very inefficient.
 
2. Avoid using dynamic libraries.

    The lib folder contains dynamic library folders, but will not contain any files.

    I deliberately avoid using dll for stability.
    
    This code has no binary purpose, is to be built by implanting it into another code.
    

    Therefore, using dynamic libraries faced a number of miscellaneous problems,
    
    most of which were minorly different environments, making it impossible to build.


    I think it may be a problem that I lack experience in, but the conclusion that I made at the moment is that I should avoid using dynamic libraries.

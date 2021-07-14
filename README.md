# Cpp Reference

C++ libraries are complex, fragmented, and hard to find well abstracted libraries.

my personal library is easy to use.(especially useful for beginner)

any comments on the source code are welcome.


# 1. License

![WTFPL](https://i.imgur.com/nAsQFRo.png) 

<h3 align="center">DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE</h1>

However, additional libraries have been installed.

Please check the libraries below, as they are licensed individually.

- [Cryptopp 8.5.0](https://github.com/weidai11/cryptopp)

# 2. Environment


OS : Windows 10

Complier : C++17 / x64

Visual Studio : 2019 / MTd


I prefer to use the latest version.

whenever official versions of Windows OS, C++, Visual Studio, etc. are updated,

I will check the compatibility and update repositories

# 3. Caution

this code was created without thinking of continuous calls.

for this reason, some functions require modifications when used for the following purposes.

1. When analyzing large amounts of data.

    The cyp::vector::isContain() = has a time complexity of O(n). This is very inefficient.

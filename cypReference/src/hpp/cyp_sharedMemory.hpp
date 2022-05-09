#pragma once
#include "cyp_common.hpp"
#include <windows.h>

namespace cyp
{
	namespace sharedMemory
	{
		/* 
		* CAUTION
		* shared memory cannot expand its size dynamically.
		* avoid using dynamically assignable types like std::string.
		* even when allocating class pointer, do not use dynamically assignable types within a class.
		*/
		template <typename T>
		class Server
		{
		private:
			void * _hmapFile;
			T* _pBuf;

		public:
			~Server()
			{
				CloseHandle(_hmapFile);
				UnmapViewOfFile(_pBuf);
			}

			Server() 
			{
				_hmapFile = nullptr;
				_pBuf = nullptr;
			}

			bool Start(std::string key, DWORD fileAccess = FILE_MAP_ALL_ACCESS)
			{
				_hmapFile = CreateFileMapping(
					INVALID_HANDLE_VALUE, NULL,
					PAGE_READWRITE, 0,
					64, key.c_str());

				if (_hmapFile == NULL)
					return false;

				_pBuf = (T *)MapViewOfFile(_hmapFile, fileAccess, 0, 0, 0);

				if (!_pBuf)
				{
					if (_hmapFile)
						CloseHandle(_hmapFile);
					return false;
				}

				return true;
			}

			void Update(T* instance)
			{
				CopyMemory((PVOID)_pBuf, instance, sizeof(T));
			}

			T* GetMemory()
			{
				if (_pBuf == nullptr)
				{
					// add error process
 				}

				return _pBuf;
			}
		};

		template <typename T>
		class Client
		{
		private:
			void* _hmapFile;
			T* _pBuf;

		public:
			~Client()
			{
				CloseHandle(_hmapFile);
				UnmapViewOfFile(_pBuf);
			}

			Client()
			{
				_hmapFile = nullptr;
				_pBuf = nullptr;
			}

			bool Start(std::string key, DWORD fileAccess = FILE_MAP_READ)
			{
				_hmapFile = OpenFileMapping(fileAccess, FALSE, key.c_str());

				if (!_hmapFile)
					return false;

				_pBuf = (T *)MapViewOfFile(_hmapFile, fileAccess, 0, 0, 0);

				if (!_pBuf)
				{
					if (_hmapFile)
						CloseHandle(_hmapFile);
					return false;
				}
			}

			T* GetMemory()
			{
				if (_pBuf == nullptr)
				{
					// add error process
				}

				return _pBuf;
			}
		};
	}
}

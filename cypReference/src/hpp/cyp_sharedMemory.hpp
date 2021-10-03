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
		* even when allocating class poiCnters, do not use dynamically assignable types within a class.
		*/
		template <typename T>
		class Server
		{
		private:
			void * hmapFile;
			T* pBuf;

		public:
			~Server()
			{
				CloseHandle(hmapFile);
				UnmapViewOfFile(pBuf);
			}

			Server(int maximumSize = 0)
			{
				hmapFile = nullptr;
				pBuf = nullptr;
			}

			bool start(std::string key, DWORD fileAccess = FILE_MAP_ALL_ACCESS)
			{
				hmapFile = CreateFileMapping(
					INVALID_HANDLE_VALUE, NULL,
					PAGE_READWRITE, 0,
					64, key.c_str());

				if (hmapFile == NULL)
					return false;

				pBuf = (T *)MapViewOfFile(hmapFile, fileAccess, 0, 0, 0);

				if (!pBuf)
				{
					if (hmapFile)
						CloseHandle(hmapFile);
					return false;
				}

				return true;
			}

			T* getMemory()
			{
				if (pBuf == nullptr)
				{
					// add error process
 				}

				return pBuf;
			}
		};

		template <typename T>
		class Client
		{
		private:
			void* hmapFile;
			T* pBuf;

		public:
			~Client()
			{
				CloseHandle(hmapFile);
				UnmapViewOfFile(pBuf);
			}

			Client()
			{
				hmapFile = nullptr;
				pBuf = nullptr;
			}

			bool start(std::string key, DWORD fileAccess = FILE_MAP_READ)
			{
				hmapFile = OpenFileMapping(fileAccess, FALSE, key.c_str());

				if (!hmapFile)
					return false;

				pBuf = (T *)MapViewOfFile(hmapFile, fileAccess, 0, 0, 0);

				if (!pBuf)
				{
					if (hmapFile)
						CloseHandle(hmapFile);
					return false;
				}
			}

			T* getMemory()
			{
				if (pBuf == nullptr)
				{
					// add error process
				}

				return pBuf;
			}
		};
	}
}
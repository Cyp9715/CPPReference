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
		*
		* RaceCondition may occur when concurrently accessing shared memory.
		* Therefore, in order to access the same memory at the same time, 
		* it is necessary to write an appropriate management mechanism.
		*/
		template <typename T>
		class SharedMemory
		{
		private:
			void * _hmapFile;
			T* _pBuf;

		public:
			~SharedMemory()
			{
				CloseHandle(_hmapFile);
				UnmapViewOfFile(_pBuf);
			}

			SharedMemory() 
			{
				_hmapFile = nullptr;
				_pBuf = nullptr;
			}

			bool Install(std::string key, DWORD fileAccess = FILE_MAP_ALL_ACCESS)
			{
				_hmapFile = CreateFileMappingA(
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
	}
}

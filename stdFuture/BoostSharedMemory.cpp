#include "stdafx.h"
#include "BoostSharedMemory.h"

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/thread/thread.hpp>
#include <fstream>
#include <iostream>

#include "timer.h"
using namespace std;
using namespace boost::interprocess;
CBoostSharedMemory::CBoostSharedMemory()
{
}


CBoostSharedMemory::~CBoostSharedMemory()
{
}

int CBoostSharedMemory::file_mapping_test()
{
//	const char* FileName = "C:\\WXGWorkDir\\filemapping\\wxgtest.bin";
//	std::size_t page_size = mapped_region::get_page_size();
//	file_mapping::remove(FileName);
//	const std::size_t frame_size = 1920 * 1080 * 4 * 25 * 10;  //10秒2，073，600，000
//	const std::size_t FileSize = 100*1024 * page_size;   //6.4GB
//	{
//		//Create a file
//		std::filebuf fbuf;
//		fbuf.open(FileName, std::ios_base::in | std::ios_base::out
//			| std::ios_base::trunc | std::ios_base::binary);
//		//Set the size
//		// 将文件位移指针 以文件的起始位置开始移动指向文件中最后一个字节上
//		fbuf.pubseekoff(FileSize - 1, std::ios_base::beg);
//		// 将文件中最后一个字节的数据置为数值 0
//		fbuf.sputc(0);
//	}
//	//remove file on exit
//	struct file_remove
//	{
//		file_remove(const char* FileName)
//			:fileName_(FileName) {}
//		~file_remove() { file_mapping::remove(fileName_); }
//		const char* fileName_;
//	}destroy_on_exit(FileName);
//
//	{
//		struct item {
//			double d1;
//			int n1;
//			float f1;
//		};
//
//		//Create file mapping
//		file_mapping m_file(FileName, read_write);
//		//Map the whole file with read-write permissions in this process
//		try
//		{
//			mapped_region region(m_file, read_write,0,frame_size);//
//			//Get the address of the mapped region
//			void* addr = region.get_address();
//			std::size_t size = region.get_size();
//			//Write all the memory to 1
//			memset(addr, 1, size);
//			region.flush();
//			std::cout << "memory allocate 001 ";
//
//			mapped_region region_01(m_file, read_write, frame_size - 1, frame_size);
//			void * addr_01 = region_01.get_address();
//			std::size_t size_01 = region_01.get_size();
//			memset(addr_01, 2, size_01);
//			region_01.flush();
//			std::cout << "memory allocate 002 ";
//		}
//		catch (boost::interprocess::interprocess_exception& ex)
//		{
//			std::cout << "\n mapped_region exception.what:" << ex.what() << endl;
//		}
//	}
//
//	//测试打开情况
//	{
//		//Open the file mapping and map it as read-only
//		file_mapping m_file_1(FileName, read_only);
//		mapped_region region(m_file_1, read_only);
//		void* addr = region.get_address();
//		std::size_t size = region.get_size();
//		const char* mem = static_cast<char*>(addr);
//		BYTE* tem = new BYTE(8294400);
//		for (std::size_t i = 0; i < 25 * 10; i++)
//		{
//			memcpy(tem, mem, 8294400);
//			mem += 8294400;
//		}
//		delete tem;
//		std::cout << "memory allocate 010 ";
//	}
	return 1;
}

int CBoostSharedMemory::file_mapping_test_01()
{
	const char* FileName = "C:\\WXGWorkDir\\wxgtest.bin";
	std::size_t page_size = mapped_region::get_page_size();
	file_mapping::remove(FileName);
	const std::size_t  sizePerFrame = 1920 * 1080 * 4;;//8294400
	const std::size_t  sizePerSecond = sizePerFrame * 25;  //1秒207,360,000
	const std::size_t FileSize = 100 * 1024 * page_size;   //6.4GB
	{
		//Create a file
		std::filebuf fbuf;
		fbuf.open(FileName, std::ios_base::in | std::ios_base::out
			| std::ios_base::trunc | std::ios_base::binary);
		//Set the size
		// 将文件位移指针 以文件的起始位置开始移动指向文件中最后一个字节上
		fbuf.pubseekoff(FileSize - 1, std::ios_base::beg);
		// 将文件中最后一个字节的数据置为数值 0
		fbuf.sputc(0);
	}
	//remove file on exit
	struct file_remove
	{
		file_remove(const char* FileName)
			:fileName_(FileName) {}
		~file_remove() { file_mapping::remove(fileName_); }
		const char* fileName_;
	}destroy_on_exit(FileName);
	
	//Create file mapping
	file_mapping m_file(FileName, read_write);	

	int FlushTime = 5;  //10秒钟
	mapped_region region(m_file, read_write, 0, sizePerSecond*FlushTime);
	//Get the address of the mapped region
	void* addr = region.get_address();
	std::size_t size = region.get_size();
	BYTE* dst = static_cast<BYTE*>(addr);

	mapped_region region_01(m_file, read_write, sizePerSecond*FlushTime, sizePerSecond*FlushTime);
	void* addr_01 = region_01.get_address();
	BYTE* src = static_cast<BYTE*>(addr_01);

	//boost::thread thrd01(boost::bind(&CBoostSharedMemory::thrd, this));

	int loopCount = 100;
	while(loopCount > 0){
		//timer frame_timer;
		BYTE* srcTem = src;
		BYTE* dstTem = dst;
		for (int i = 0; i < FlushTime*25; i++)
		{
			timer frame_timer;
			memcpy(dstTem, srcTem, sizePerFrame);
			srcTem += sizePerFrame;
			dstTem += sizePerFrame;
			//if (i%5 == 0)
			{
				Sleep(40);
				region.flush(); //不flush就不写磁盘
				double frameTime = frame_timer.elapsed();
				std::cout << "write write write  " << frameTime << " per 5 frames  loopCount   " << loopCount << endl;
			}

		}
		//region.flush();
		//double frameTime = frame_timer.elapsed();
		//std::cout << "write write write  " << frameTime << " per 5 second  loopCount   " << loopCount << endl;
		loopCount--;
	}
	Sleep(300);
	return 1;
}

void CBoostSharedMemory::thrd()
{
	const char* FileName = "C:\\WXGWorkDir\\wxgtest.bin";
	std::size_t page_size = mapped_region::get_page_size();
	//file_mapping::remove(FileName);
	const std::size_t  sizePerFrame = 1920 * 1080 * 4;;//8294400
	const std::size_t  sizePerSecond = sizePerFrame * 25;  //1秒207,360,000
	const std::size_t FileSize = 100 * 1024 * page_size;   //6.4GB
	int FlushTime = 10;  //10秒钟
	int loopCount = 20;
	file_mapping fileMap(FileName, read_write);
	while (loopCount > 0) {
		//timer frame_timer;
		//Open the file mapping and map it as read-only
		mapped_region region(fileMap, read_only, 0, sizePerSecond*FlushTime);
		void* addr = region.get_address();
		std::size_t size = region.get_size();
		BYTE* src = static_cast<BYTE*>(addr);

		mapped_region region_02(fileMap, read_write, 2*sizePerSecond*FlushTime, sizePerSecond*FlushTime);
		void* addr_02 = region_02.get_address();
		BYTE* dst = static_cast<BYTE*>(addr_02);

		BYTE* srcTem = src;
		BYTE* dstTem = dst;
		for (int i = 0; i < FlushTime * 25; i++)
		{
			timer frame_timer;
			memcpy(dstTem, srcTem, sizePerFrame);
			srcTem += sizePerFrame;
			dstTem += sizePerFrame;
			double frameTime = frame_timer.elapsed();
			if (i % 5 == 0)
				std::cout << "				read read read  " << frameTime << " per frame loopCount  " << loopCount << endl;
		}

		//double frameTime = frame_timer.elapsed();
		//std::cout << "				read read read  " << frameTime << "  loopCount  " << loopCount << endl;
		loopCount--;
	}
	std::cout << "read end! " << endl;
}

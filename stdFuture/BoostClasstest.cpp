#include "stdafx.h"
#include "BoostClasstest.h"
#include <boost/thread/thread.hpp>
#include <boost/function/function0.hpp>
#include <boost/function/function1.hpp>
#include <boost/function/function2.hpp>
#include <boost/function/function3.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/filesystem.hpp>

#include <boost/lexical_cast.hpp>
#include "../utility/utf8conv.h"

#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>//std::system
#include <sstream>

#include <boost/interprocess/containers/vector.hpp>  
#include <boost/interprocess/allocators/allocator.hpp> 
#include <boost/format.hpp>
#include <string>
#include <vector>

#include <inttypes.h>

#include <boost/algorithm/string/case_conv.hpp>

#include "thread_specific_ptr.h"

CBoostClasstest::CBoostClasstest()
{
}


CBoostClasstest::~CBoostClasstest()
{
}

void CBoostClasstest::hello()
{
	std::cout << "Hello world, I'm a thread !" << std::endl;
}

void CBoostClasstest::helloWorld(std::string& str)
{
	std::cout << str << std::endl;
}

void CBoostClasstest::helloWorld(int str, std::string& str1, std::string& str2)
{
	std::cout << str << str1 << str2 << std::endl;
}

void CBoostClasstest::helloWorld(int str, std::string& str1)
{
	std::cout << str << str1 <<  std::endl;
}

struct A {
	void func(int x, int y) {
		std::cout << x << "," << y << std::endl;
	}
};
bool some_func(int i, double d) {
	return i > d;
}
int CBoostClasstest::simpleThread()
{
	boost::thread thrd(&CBoostClasstest::hello, this);  //这就有个问题，怎么绑定hello的重载函数呢？
	thrd.join();

	thrd = boost::thread(&CBoostClasstest::hello, this);
	thrd.join();

	boost::function0<void> f = boost::bind(&CBoostClasstest::hello, this);
	boost::thread thrd0(f);
	thrd0.join();
	thrd0.join();  //验证多次join会不会有问题

	boost::thread testThread;
	testThread.join();  //验证现场没有启动会不会等待

	//test bind function
	//要向像 A::func 这样的非静态成员函数绑定.
	//若A::func有n个参数, 则 bind 要有 n + 2 个参数: 指向成员函数fun的指针, 绑定到this的对象, n个参数
	A a;
	A* pa = new A;
	boost::shared_ptr<A> ptr_a(pa);
	boost::bind(&A::func, a, 3, 4)();    //输出 3, 4
	boost::bind(&A::func, pa, 3, 4)();   //输出 3, 4
	boost::bind(&A::func, ptr_a, 3, 4)();//输出 3, 4

	boost::bind(&A::func, _1, 3, 4)(ptr_a);//输出 3, 4
	//可以看出.不论传递给bind 的第2个参数是 对象.对象指针.还是智能指针.bind函数都能够正常工作
	std::string str = "wang";
	std::string str1;
	
	//boost::function<void(std::string)> f1 = boost::bind(&CBoostClasstest::helloWorld, this,_1);
	boost::function1<void,std::string> f11 = boost::bind(&CBoostClasstest::helloWorld, this, str);
	//f1(str);
	f11(str);

	typedef boost::function<void(std::string)> Fun1;
	typedef boost::function<void(int,std::string)> Fun2;
	Fun2 dd;
	boost::function<void(int, std::string, std::string)> f3 = boost::bind(&CBoostClasstest::helloWorld, this, 17,str,str);
	boost::function3<void,int,std::string,std::string> ff3 = boost::bind(&CBoostClasstest::helloWorld, this, 5, str, str);
	boost::bind(&CBoostClasstest::helloWorld, this, _1, _2)(19, str);
	boost::bind(&CBoostClasstest::helloWorld, this, _1, _2, _3)(10,str,str);
	boost::thread thrd2(f11,str);
	thrd2.join();

	return 0;
}

void CBoostClasstest::FileParser(const std::wstring& strFileName)
{
	namespace fs = boost::filesystem;
	using namespace boost::property_tree;
	boost::property_tree::wptree pt;
	std::wstring strFileNameTem = _T("FamousServer.config");
	try
	{
		auto initialPath = fs::initial_path<fs::path>().wstring();
		std::wifstream file(initialPath + _T("\\") + strFileNameTem);
		//boost::property_tree::read_xml(file, pt, boost::property_tree::xml_parser::trim_whitespace | boost::property_tree::xml_parser::no_comments);
		boost::property_tree::read_xml(file, pt, boost::property_tree::xml_parser::trim_whitespace);
		auto paths = pt.get_child(L"configuration.paths");
		std::wstring mediaPath = paths.get<std::wstring>(L"media-path", L"F:\\clips");
		std::wcout << mediaPath << std::endl;

		paths.put(L"media-path", L"M:\\clips");
		std::wstring mediaPath01 = paths.get<std::wstring>(L"media-path", L"F:\\clips");
		std::wcout << mediaPath01 << std::endl;
		xml_parser::xml_writer_settings<std::wstring> settings(' ', 3, _T("utf-8"));
		//std::wstringstream fileName(initialPath + _T("\\") + strFileNameTem);
		std::string fileName = utf8util::UTF8FromUTF16(initialPath + _T("\\") + strFileNameTem);
		//std::wcout << fileName.str().c_str() << std::endl;
		pt.put_child(L"configuration.paths", paths);
		boost::property_tree::xml_parser::write_xml(fileName, pt, std::locale(), settings);

	}
	catch (...)
	{
		std::wcout << L" ### Invalid configuration file. ###";
		throw;
	}

}

template <typename ElemT>
struct HexTo {
	ElemT value;
	operator ElemT() const { return value; }
	friend std::wistream& operator >> (std::wistream& in, HexTo& out) {
		in >> std::hex >> out.value;
		return in;
	}
};
void CBoostClasstest::Convert16StringTodata()
{
	int x = boost::lexical_cast<HexTo<int>>(L"A0");
	int a = 0;

	std::wstring str = L"IP2110-out";
	boost::to_lower(str);
	std::wstring str01 = boost::to_upper_copy(str);
}

void CBoostClasstest::thread_specific_ptrClassTest()
{
	// 主线程也需要本地存储一个对象
	thread_ptr::thread_specific_ptrClass ptrClass;

	ptrClass.get_thread_logfile().reset(new thread_ptr::logfile(100));
	// 记录日志
	ptrClass.get_thread_logfile()->log("程序开始");
	random::uniform_int_distribution<int>  waittime(100, 500);
	random::mt19937 gen;



	// 创建一个线程组
	thread_group tg;
	for (int i = 0; i < 5; ++i)
	{
		//tg.create_thread(boost::bind(&thread_ptr::thread_specific_ptrClass::run,ptrClass, i));

		boost::posix_time::milliseconds wt(waittime(gen));
		boost::this_thread::sleep(wt);
	}
	// 等待所有线程结束
	tg.join_all();
	ptrClass.get_thread_logfile()->log("程序结束");
	// 显示最终合并得到的日志文件
	//thread_ptr::cmblog->display();
}

	//使用共享内存做为一个匿名内存块池
	int CBoostClasstest::share_memory_001()
	{
		return 0;
		//using namespace boost::interprocess;
		//{
		//	//Remove shared memory on construction and destruction  
		//	struct shm_remove
		//	{
		//		shm_remove() { shared_memory_object::remove("MySharedMemory"); }
		//		~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
		//	}remover;

		//	//Create a managed shared memory segment  
		//	managed_shared_memory segment(create_only, "MySharedMemory", 65536);

		//	//Allocate a portion of the segment (raw memory)  
		//	managed_shared_memory::size_type free_memory = segment.get_free_memory();
		//	void * shptr = segment.allocate(1024/*bytes toallocate*/);

		//	//Check invariant  
		//	if (free_memory <= segment.get_free_memory())
		//		return 1;

		//	//An handle from the base address can identify any byte of the shared  
		//	//memory segment even if it is mapped indifferent base addresses  
		//	managed_shared_memory::handle_t handle = segment.get_handle_from_address(shptr);
		//	std::stringstream s;
		//	//s << "abc.exe" << " " << handle; //为了编译通过
		//	s << std::ends;

		//	//Launch child process  
		//	if (0 != std::system(s.str().c_str()))
		//		return 1;
		//	//Check memory has been freed  
		//	if (free_memory != segment.get_free_memory())
		//		return 1;
		//}

		////使用的时候，会通过名字打开
		//{
		//	//Open managed segment  
		//	managed_shared_memory segment(open_only, "MySharedMemory");

		//	//An handle from the base address can identify any byte of the shared  
		//	//memory segment even if it is mapped indifferent base addresses  
		//	managed_shared_memory::handle_t handle = 0;

		//	//Obtain handle value  
		//	std::stringstream s;
		//	/*s << argv[1]; */  //为了编译通过
		//	s >> handle;

		//	//通过传handle进行共享
		//	//Get buffer local address from handle  
		//	void *msg = segment.get_address_from_handle(handle);

		//	//Deallocate previously allocated memory  
		//	segment.deallocate(msg);
		//}
	}


	//创建命名共享内存对象
	//你可以在共享内存段中创建对象，给它们string类型的名字以便其他进程能够找到它们，使用它们，并且当对象不再使用时从内存段中删除它们

	//int CBoostClasstest::share_memory_002()
	//{
	//	using namespace boost::interprocess;
	//	typedef std::pair<double, int> MyType;
	//
	//	{
	//		//Remove shared memory on construction and destruction  
	//		struct shm_remove
	//		{
	//			shm_remove() { shared_memory_object::remove("MySharedMemory"); }
	//			~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
	//		} remover;
	//
	//		//Construct managed shared memory  
	//		managed_shared_memory segment(create_only, "MySharedMemory", 65536);
	//
	//		//Create an object of MyType initialized to {0.0, 0}  
	//		MyType *instance = segment.construct<MyType>
	//			("MyType instance")  //name of the object  
	//			(0.0, 0);            //ctor first argument 
	//								 //Create an array of 10 elements of MyType initialized to {0.0, 0}  
	//
	//		MyType *array = segment.construct<MyType>
	//			("MyType array")     //name of the object  
	//			[10]                 //number of elements  
	//		(0.0, 0);            //Same two ctor arguments for all objects 
	//
	//		//Create an array of 3 elements of MyType initializing each one  
	//		//to a different value {0.0, 0}, {1.0, 1}, {2.0, 2}...  
	//		float float_initializer[3] = { 0.0, 1.0, 2.0 };
	//		int   int_initializer[3] = { 0, 1, 2 };
	//
	//		MyType *array_it = segment.construct_it<MyType>
	//			("MyType array from it")   //name of the object  
	//			[3]                        //number of elements  
	//		(&float_initializer[0]    //Iterator for the 1st ctor argument  
	//			, &int_initializer[0]);    //Iterator for the 2nd ctor argument 
	//									   //Launch child process  
	//		std::string s(argv[0]); s += " child ";
	//		if (0 != std::system(s.c_str()))
	//			return 1;
	//
	//		//Check child has destroyed all objects  
	//		if (segment.find<MyType>("MyType array").first ||
	//			segment.find<MyType>("MyType instance").first ||
	//			segment.find<MyType>("MyType array from it").first)
	//			return 1;
	//	}
	//	{
	//		//Open managed shared memory  
	//		managed_shared_memory segment(open_only, "MySharedMemory");
	//
	//		std::pair<MyType*, managed_shared_memory::size_type> res;
	//
	//		//Find the array  
	//		res = segment.find<MyType>("MyType array");
	//		//Length should be 10  
	//		if (res.second != 10) return 1;
	//
	//		//Find the object  
	//		res = segment.find<MyType>("MyType instance");
	//		//Length should be 1  
	//		if (res.second != 1) return 1;
	//
	//		//Find the array constructed from iterators  
	//		res = segment.find<MyType>("MyType array from it");
	//		//Length should be 3  
	//		if (res.second != 3) return 1;
	//
	//		//We're done, delete all the objects  
	//		segment.destroy<MyType>("MyType array");
	//		segment.destroy<MyType>("MyType instance");
	//		segment.destroy<MyType>("MyType array from it");
	//	}
	//}
	//
	////Boost.Interprocess提供offset_ptr智能指针家族做为一个偏移指针，它用来存储偏移指针地址与对象地址的距离。当offset_ptr置于共享内存段中时，
	////它能安全的指向这块共享内存段中的对象，甚至当内存段在不同的进程映射到不同的基地址时也能正常工作。
	////这使得带指针成员的对象能够放置在共享内存中。例如，如果我们想在共享内存中创建一个链表
	//int CBoostClasstest::share_memory_003()
	//{
	//	using namespace boost::interprocess;
	//
	//	//Shared memory linked list node  
	//	struct list_node
	//	{
	//		offset_ptr<list_node> next;
	//		int                   value;
	//	};
	//
	//	//Remove shared memory on construction and destruction  
	//	struct shm_remove
	//	{
	//		shm_remove() { shared_memory_object::remove("MySharedMemory"); }
	//		~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
	//	} remover;
	//
	//	//Create shared memory  
	//	managed_shared_memory segment(create_only,
	//		"MySharedMemory",  //segment name  
	//		65536);
	//
	//	//Create linked list with 10 nodes in shared memory  
	//	offset_ptr<list_node> prev = 0, current, first;
	//
	//	int i;
	//	for (i = 0; i < 10; ++i, prev = current) {
	//		current = static_cast<list_node*>(segment.allocate(sizeof(list_node)));
	//		current->value = i;
	//		current->next = 0;
	//
	//		if (!prev)
	//			first = current;
	//		else
	//			prev->next = current;
	//	}
	//
	//	//Communicate list to other processes  
	//	//. . .  
	//	//When done, destroy list  
	//	for (current = first; current; /**/) {
	//		prev = current;
	//		current = current->next;
	//		segment.deallocate(prev.get());
	//	}
	//
	//}
	//
	////http://blog.csdn.net/great3779/article/details/7222202
	///*Boost.Interprocess允许在共享内存和内存映射文件中创建复杂的对象。例如，我们可以在共享内存中
	//创建类STL容器。为了做到这点，我们仅需创建一个特殊（控制）的共享内存片段，申明一个
	//Boost.Interprocess分配器然后创建像其他对象一样在共享内存中创建vector*/
	//
	//using namespace boost::interprocess;
	//using namespace std;
	//int CBoostClasstest::share_memory_004()
	//{
	//
	//	//Define an STL compatible allocator of ints that allocates from the managed_shared_memory.  
	//	//This allocator will allow placing containers in the segment  
	//	typedef allocator<int, managed_shared_memory::segment_manager>  ShmemAllocator;
	//
	//	//Alias a vector that uses the previous STL-like allocator so that allocates  
	//	//its values from the segment  
	//	typedef vector<int, ShmemAllocator> MyVector;
	//
	//	{
	//		struct shm_remove
	//		{
	//			shm_remove() { shared_memory_object::remove("MySharedMemory"); }
	//			~shm_remove() { shared_memory_object::remove("MySharedMemory"); }
	//		} remover;
	//
	//		//Create a new segment with given name and size  
	//		boost::interprocess::managed_shared_memory segment(create_only, "MySharedMemory", 65536);
	//
	//		//Initialize shared memory STL-compatible allocator  
	//		const ShmemAllocator alloc_inst(segment.get_segment_manager());
	//
	//		//Construct a vector named "MyVector" in shared memory with argument alloc_inst  
	//		MyVector *myvector = segment.construct<MyVector>("MyVector")(alloc_inst);
	//
	//		for(int i = 0; i < 100; ++i)  //Insert data in the vector  
	//			myvector->push_back(i);
	//
	//		//Launch child process  
	//		std::string s(argv[0]);
	//		s += " child ";
	//		if(0 != std::system(s.c_str()))
	//			return 1;
	//
	//		//Check child has destroyed the vector  
	//		if(segment.find<MyVector>("MyVector").first)
	//			return 1;
	//	}
	//
	//
	//	{
	//		//Child process  
	//		//Open the managed segment  
	//		managed_shared_memory segment(open_only, "MySharedMemory");
	//
	//		//Find the vector using the c-string name  
	//		MyVector *myvector = segment.find<MyVector>("MyVector").first;
	//
	//		//Use vector in reverse order  
	//		std::sort(myvector->rbegin(), myvector->rend());
	//
	//		//When done, destroy the vector from the segment  
	//		segment.destroy<MyVector>("MyVector");
	//	}
	//}

int CBoostClasstest::hardware()
{
	int hardware_concurrency_ = boost::thread::hardware_concurrency();
	return 0;
}

void CBoostClasstest::boostFormatString()
{
	std::string str = (boost::format("%1% \n %2% \n %3%") % "first"%"second"%"third").str();
	boost::format fmt("%2% \n %1% \n %3%");
	fmt%"first";
	fmt %"second";
	fmt %"third";
	std::string str01 = fmt.str();

	//传统c语言风格  
	cout << boost::format("\n\n%s"
		"%1t 十进制 = [%d]\n"
		"%1t 格式化的十进制 = [%5d]\n"
		"%1t 格式化十进制，前补'0' = [%05d]\n"
		"%1t 十六进制 = [%x]\n"
		"%1t 八进制 = [%o]\n"
		"%1t 浮点 = [%f]\n"
		"%1t 格式化的浮点 = [%3.3f]\n"
		"%1t 科学计数 = [%e]\n"
	) % "example :\n" % 15 % 15 % 15 % 15 % 15 % 15.01 % 15.01 % 15.01 << endl;

	//.net的风格  
	cout << boost::format("%1%"
		"%1t 十进制 = [%2$d]\n"
		"%1t 格式化的十进制 = [%2$5d]\n"
		"%1t 格式化十进制，前补'0' = [%2$05d]\n"
		"%1t 十六进制 = [%2$x]\n"
		"%1t 八进制 = [%2$o]\n"
		"%1t 浮点 = [%3$f]\n"
		"%1t 格式化的浮点 = [%3$3.3f]\n"
		"%1t 科学计数 = [%3$e]\n"
	) % "example :\n" % 15 % 15.01 << endl;


	try
	{
		//另外还支持 %|spec| 格式 ，它与%spec没有功能上的区别，只是看的更清楚了。
		std::cout << boost::format("%|1$+| %2% %1%") % 99 % 100 << std::endl;
		std::cout << boost::format("%|+| %|| %||") % 99 % 100 % 99 << std::endl;//省略占位符
		std::cout << boost::format("%+d %d %d") % 99 % 100 % 99 << std::endl;
		std::cout << boost::format("%+s %s %s") % 99 % 100 % 99 << std::endl;
	}
	catch (boost::io::format_error &ex)
	{
		std::cout << ex.what() << std::endl;
	}

	//   %|5$x|


	boost::format fmt2("%s:%d + %d = %d\n");
	fmt2%"sum" % 1 % 2 % (1 + 2);
	cout << fmt2.str();
	cout << boost::format("%s:%d + %d = %d\n") % "sum" % 1 % 2 % (1 + 2);

	boost::format fmt3("%05d\n%|-8.3f|\n%| 10s|\n%05X\n");
	cout << fmt3 % 62 % 2.236%"123456" % 15;


	uint64_t oBestMasterClockId = 0x1234567890ABCDEF;
	uint64_t oGrandMasterClockId = 0x1234567890ABCDEF;

	char buf[200];
	sprintf_s(buf, _countof(buf), "Detected Smpte2059 changes:\n"
		" \tState=%s\n"
		" \tBestMasterClockSfpLabel=%s\n"
		" \tBestMasterClockId=%016" PRIx64 "\n"
		" \tGrandMasterClockId=%016" PRIx64 "\n",
		"abc",
		"def",
		oBestMasterClockId,
		oGrandMasterClockId);
	cout << buf;

	auto currentTime = boost::get_xtime(boost::get_system_time());
	boost::posix_time::ptime pTime = boost::posix_time::from_time_t(currentTime.sec);
	//std::tm timestamp = boost::posix_time::to_tm(pTime);
	auto date = pTime.date();
	auto time = pTime.time_of_day();
	auto milliseconds = time.fractional_seconds() / 1000; // microseconds to milliseconds

	std::wstringstream buffer;
	buffer
		<< std::setfill(L'0')
		<< L"["
		<< std::setw(4) << date.year() << L"-" << std::setw(2) << date.month().as_number() << "-" << std::setw(2) << date.day().as_number()
		<< L" "
		<< std::setw(2) << time.hours() << L":" << std::setw(2) << time.minutes() << L":" << std::setw(2) << time.seconds()
		<< L"."
		<< std::setw(3) << milliseconds
		<< L"] ";
	wcout << buffer.str();
}

// shared_ptr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>
#include <vector>
#include <string>
#include <assert.h>
#include <vector>
struct Base
{
	Base() { std::cout << "  Base::Base()\n";}
	// Note: non-virtual destructor is OK here
	~Base() { std::cout << "  Base::~Base()\n"; }
};

struct Derived : public Base
{
	Derived() { std::cout << "  Derived::Derived()\n"; }
	~Derived() { std::cout << "  Derived::~Derived()\n"; }
};

void thr(std::shared_ptr<Base> p)
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::shared_ptr<Base> lp = p; // thread-safe, even though the
								  // shared use_count is incremented
	{
		static std::mutex io_mutex;
		std::lock_guard<std::mutex> lk(io_mutex);
		std::cout << "local pointer in a thread:\n"
			<< "  lp.get() = " << lp.get()
			<< ", lp.use_count() = " << lp.use_count() << '\n';
	}
}

class shared                                    //一个拥有shared_ptr的类    
{
private:
	std::shared_ptr<int> p;                          //shared_ptr成员变量    
public:
	shared(std::shared_ptr<int> p_) :p(p_) {}          //构造函数初始化shared_ptr        
	void print()                                //输出shared_ptr的引用计数和指向的值        
	{
		std::cout << "count:" << p.use_count()
			<< " v =" << *p << std::endl;
	}
};

void print_func(std::shared_ptr<int> p)                //使用shared_ptr作为函数参数    
{
	//同样输出shared_ptr的引用计数和指向的值        
	std::cout << "count:" << p.use_count()
		<< " v=" << *p << std::endl;
}

int main()
{
	{
		std::shared_ptr<Base> p = std::make_shared<Derived>();  //调用没有参数的构造函数

		std::cout << "Created a shared Derived (as a pointer to Base)\n"
			<< "  p.get() = " << p.get()
			<< ", p.use_count() = " << p.use_count() << '\n';
		std::thread t1(thr, p), t2(thr, p), t3(thr, p);
		p.reset(); // release ownership from main
		t1.join(); t2.join(); t3.join();
		std::cout << "Shared ownership between 3 threads and released\n"
			<< "ownership from main:\n"
			<< "  p.get() = " << p.get()
			<< ", p.use_count() = " << p.use_count() << '\n';

		std::cout << "All threads completed, the last one deleted Derived\n";
	}
	{
		std::shared_ptr<std::string> sp = std::make_shared<std::string>(("make_shared"));
		std::cout << *sp << std::endl;
		std::shared_ptr<std::string> sp1(new std::string(("make_shared_new")));
		std::cout << *sp1 << std::endl;
		std::cout << sp->size() << std::endl;
	}
	{
		std::shared_ptr<int> sp100(new int(10));                //一个指向整数的shared_ptr    
		assert(sp100.unique());                            //现在shared_ptr是指针的唯一持有者     
		std::shared_ptr<int> sp200 = sp100;                       //第二个shared_ptr,拷贝构造函数     
		assert(sp100 == sp200 && sp100.use_count() == 2);       //两个shared_ptr相等,指向同一个对象,引用计数为2    
		*sp200 = 100;                                     //使用解引用操作符修改被指对象    
		assert(*sp100 == 100);                             //另一个shared_ptr也同时被修改     
		sp100.reset();                                     //停止shared_ptr的使用    
		assert(!sp100);                                     //sp不再持有任何指针(空指针)
	}

	{
		std::shared_ptr<int> pt = std::make_shared<int>(100);
		shared s1(pt), s2(pt);
		s1.print();
		s2.print();
		*pt = 20;
		print_func(pt);
		s1.print();
	}

	{
		typedef std::vector<std::shared_ptr<int>> vs;//一个持有shared_ptr的标准容器类型  
		vs v(10);                                   //声明一个拥有10个元素的容器，元素被初始化为空指

		int i = 0;
		for (vs::iterator pos = v.begin(); pos != v.end(); ++pos)
		{
			(*pos) = std::make_shared<int>(++i);     //使用工厂函数赋值            
			std::cout << *(*pos) << ", ";            //输出值        
		}
		std::cout << std::endl;
		std::shared_ptr<int> p = v[9];
		*p = 100;
		std::cout << *v[9] << std::endl;
	}

	system("Pause");
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////
#define SAFE_DELETE(x) do {delete x; x = NULL;} while (0);
class Meter
{
public:
	int _reference;
	Meter()
	{
		_reference = 0;
	}
};

template<typename T>
class sp
{
public:
	Meter* _meter;
	T* _raw;
	sp() :_meter(NULL), _raw(NULL)
	{

	}
	sp(T* t)
	{
		_meter = new Meter;
		this->_raw = t;
		_meter->_reference = 1; //self
	}
	sp(const sp &s)
	{
		_meter = s._meter;
		++(s._meter->_reference);
		_raw = s._raw;
	}

	template<typename S>
	sp(const sp<S> &s)
	{
		_meter = s._meter;
		++(s._meter->_reference);
		_raw = dynamic_cast<T*>(s._raw);
	}

	~sp()
	{
		if (_meter)
		{
			--(_meter->_reference);
		}
		if (_meter && _meter->_reference == 0)
		{
			SAFE_DELETE(_raw);
			SAFE_DELETE(_meter);
		}
	}

	sp & operator= (sp &sp_)
	{
		if (_raw == sp_._raw)
		{
			return *this;
		}
		_raw = sp_._raw;
		_meter = sp_._meter;
		++_meter->_reference;
		return *this;
	}

	template<typename S>
	sp<T>& operator= (sp<S> &sp_)
	{
		if (_raw == sp_._raw) return *this;
		_raw = dynamic_cast<T*> (sp_._raw);
		_meter = sp_._meter;
		++_meter->_reference;
		return *this;
	}

	T* operator*()
	{
		return this;
	}

	T* operator->()
	{
		return _raw;
	}
	
	operator bool()
	{
		return _raw != NULL;
	}
	bool operator== (sp& sp_)
	{
		return _raw == sp_._raw;
	}
	int use_count() const
	{
		if (_meter) return _meter->_reference;
		return 0;
	}
};

class baseA
{
public:
	virtual ~baseA()
	{
		std::cout << "de BaseA";
	}
};
class A :public baseA
{
public:
	int data;
	A(int d) :data(d) {}
	~A()
	{
		std::cout << data << " de A " << std::endl;
	}
};
sp<baseA > func1()
{
	return  sp<A>(new A(1));
}
sp<A > func2()
{
	sp<A>  a = sp<A>(new A(2));
	return  a;
}
int main_test()
{	
	std::vector<sp<baseA>> bs;
	bs.resize(2);
	bs[0] = func2();
	bs[1] = func1();

	sp<A> c = bs[0];
	//sp<baseA> bs;
	//bs = func1();
	return 0;
}
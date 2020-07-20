#include "stdafx.h"
#include "PlusPlus11.h"
#include <iostream>
#include <functional>
#include <list>
#include <string>
#include <vector>
#include <array>
#include <map>

#include <chrono>

#include <cctype>

using namespace std;

class base {
public:
	void func()
	{
		cout << "func1()" << endl;
	}
	void func(int x)
	{
		cout << "func2()" << endl;
	}
	void func10()
	{
		cout << "func10()" << endl;
	}
};

class son : public base {
public:
	using base::func;    //若没有此句，func()和func(int x)将会被隐藏
	void func(int x, int y)
	{
		cout << "func()3" << endl;
	}
};

void CPlusPlus11::overhide()
{
	base a;
	a.func();
	a.func(1);
	son b;
	b.func(1, 1);
	b.func();
	b.func(1);
	b.func10(); //同名覆盖，这个不同命可以直接调用基类的函数
}

void CPlusPlus11::typeID()
{
	class Base { };
	struct STU { };
		//获取一个普通变量的类型信息
		int n = 100;
		const type_info &nInfo = typeid(n);
		cout << nInfo.name() << " | " << nInfo.raw_name() << " | " << nInfo.hash_code() << endl;
		//获取一个字面量的类型信息
		const type_info &dInfo = typeid(25.65);
		cout << dInfo.name() << " | " << dInfo.raw_name() << " | " << dInfo.hash_code() << endl;
		//获取一个对象的类型信息
		Base obj;
		const type_info &objInfo = typeid(obj);
		cout << objInfo.name() << " | " << objInfo.raw_name() << " | " << objInfo.hash_code() << endl;
		//获取一个类的类型信息
		const type_info &baseInfo = typeid(Base);
		cout << baseInfo.name() << " | " << baseInfo.raw_name() << " | " << baseInfo.hash_code() << endl;
		//获取一个结构体的类型信息
		const type_info &stuInfo = typeid(struct STU);
		cout << stuInfo.name() << " | " << stuInfo.raw_name() << " | " << stuInfo.hash_code() << endl;
		//获取一个普通类型的类型信息
		const type_info &charInfo = typeid(char);
		cout << charInfo.name() << " | " << charInfo.raw_name() << " | " << charInfo.hash_code() << endl;
		//获取一个表达式的类型信息
		const type_info &expInfo = typeid(20 * 45 / 4.5);
		cout << expInfo.name() << " | " << expInfo.raw_name() << " | " << expInfo.hash_code() << endl;
}

void CPlusPlus11::generalTest()
{
	int rate1 = 73;
	int rate2 = 159;
	float exponential = rate1 / 32.0 - 2;
	double tmp = pow(10, exponential);

	float exponential_1 = rate1 + 1 / 32.0 - 2;
	double tmp1 = pow(10, exponential_1);
	float exponential_2 = rate1 / 32.0 - 2;
	double tmp2 = pow(10, exponential_2);
	double tmp3 = 256 * tmp1 * tmp2;
	double tmp4 = rate2 / tmp3;

	int  speedvalue = (int)ceil(tmp + tmp4);
	std::cout << speedvalue << endl;
}

CPlusPlus11::CPlusPlus11()
{
}


CPlusPlus11::~CPlusPlus11()
{
}

int add(int i, int j)
{
	return i + j;
}
int foo() { 
	cout << "foo()" << endl;
	return 1;
};


template<class U, class V>                  //decltype(u*v)现在是函数的返回值，靠auto来猜了
auto Multiply(U u, V v) -> decltype(u*v)    // Note -> after the function bracet.  
{
	return u*v;
}

void CPlusPlus11::decltypeTest()
{
	typeID();

	decltype(add(5, 6)) var = 5;   //decltype(add(5, 6)) 表示的是add函数的返回类型，就是int
	cout << typeid(var).name() << endl; // This will print int

	//////////////////////////////////////////////////////////////////////////
	struct M { double x; };

	double pi = 3.14;
	const M* m = new M();
	decltype((m->x)) piRef = pi;
	cout << typeid(piRef).name() << endl; // This will print int
	// Note: Due to the inner bracets the inner statement is evaluated as expression,  
	// rather than member 'x' and as type of x is double and as this is lvale  
	// the return of declspec is double& and as 'm' is a const pointer   
	// the return is actually const double&.  
	// So the type of piRef is const double& 

	//////////////////////////////////////////////////////////////////////////
	//int foo() {};
	decltype(foo()) x; // x is an int and note that   
					   // foo() is not actually called at runtime 
	                   //不会执行表达式，而用auto就会
	x = 10;
	//////////////////////////////////////////////////////////////////////////
}

void CPlusPlus11::autoTest()
{
	/////////////////////////////////////////////////////////////////////////////
	//wxg20170330
	std::map<int, int64_t>  send_to_consumers_delays;
	send_to_consumers_delays[123] = 123;
	send_to_consumers_delays[124] = 124;
	send_to_consumers_delays.erase(123);

	/////////////////////////////////////////////////////////////////////////////
	//wxg20170321
	int MAX_THREADS = 16;
	int count = 4;
	std::array<std::vector<int>, 16> jobs;
	for (int n = 0; n < count; ++n)
		jobs[n*MAX_THREADS / count].push_back(n);
	for (int i = 0;i<MAX_THREADS;++i)
	{
		for (auto k:jobs[i])  //jobs[i]是一个vector，里面只有一个元素，所以遍历一次
		{
			std::cout << "k= " << k << " jobs[" << i << "]= " << jobs[i][0] << std::endl;
		}
	}
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	//vec.insert()
	//vec.erase()
	cout << vec.front() << " " << vec.back() << endl;
	//把vector里面的东西遍历一遍，上面是因为vector里面只有一个元素
	std::fill(vec.begin(), vec.end(), -1);
	for (auto kk:vec)
	{
		cout << kk << endl;
	}
	////////////////////////////////////////////////////////////////
	auto a = 12;
	auto b = 12.0f;
	auto c = true;
	auto d = [](int x)->int { return 12; };
	auto e = std::bind(&foo/*, std::placeholders::_1*/);
	e();
	//template<typename T>
	//using Tlist = std::list<T>;
	using Tlist = std::list<char>;
	using df = void(*)();//等价于typedef void(*df)()
}

//////////////////////////////////////////////////////////////////////////
std::string readFileContent()
{
	std::string filecontent = "oldContent";
	return filecontent;
}

//右值引用的意义通常解释为两大作用：移动语义和完美转发

void CPlusPlus11::stdmove()
{

	//左值右值测试
	lValueRvalue();
	//这是一个浪费，函数的返回值被拷贝到s中后，栈上的临时变量就会白销毁
	std::string s = readFileContent();

	//C++11
	//对象ss在被赋值的时候，方法std::string::operator =(std::string&&)会被调用，符号&&告诉std::string类的编写者，
	//传入的参数是一个临时对象，可以挪用其数据，于是std::string::operator =(std::string&&)的实现代码中，会置空形参，
	//同时将原本保存在中形参中的数据移动到自身。不光是临时变量，只要是你认为不再需要的数据，都可以考虑用std::move移动
	std::string ss = std::move(readFileContent());

	string A("abc");
	string AA("abc");
	string&& Rval = std::move(A);
	string& Lval = AA;//std::move(AA);
	string B(Rval);    // this is a copy , not move.
	cout << A << endl;   // output "abc"
	string C(std::forward<string>(Rval));  // move.
	std::string D = std::forward<string>(Lval);  //这里也是一个move
	std::string E = std::forward<string>(B);  //move
	cout << A << endl;       /* output "" */
	cout << AA << endl;       /* output "" */

	string str = "asd";
	string& str1 = std::move(str);
	string str2 = std::move(str);

	//int &i = 6; // error，lvalue reference 不能引用字面常量	
				// error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
	const int &j = 6; // ok，可以将一个临时对象绑定到一个 const 的左值引用

	//X &ref_a = X(); 		// error
	//const X &ref_ca = X();	// ok，可以将一个临时对象绑定到一个 const 的左值引用

	int &&rref = 6;		// ok，rvalue reference 可以引用：字面常量
	//X &&rref_a = X();	// ok，rvalue reference 可以引用：临时对象
}
template<typename T>
void swap(T& a, T& b)
{
	T t(std::move(a)); //a为空，t占有a的初始数据
	a = std::move(b);  //b为空，a占有b的初始数据
	b = std::move(t);  //t为空，b占有a的初始数据
}
//总之，std::move是为性能而生的，正式因为了有了这个主动报告废弃物的设施，所以C++11中的STL性能大幅提升，
//即使C++用户仍然按找旧有的方式来编码，仍然能因中新版STL等标准库的强化中收益。

//////////////////////////////////////////////////////////////////////////

//左值和右值的定义
//在C++中，可以放到赋值操作符 = 左边的是左值，可以放到赋值操作符右边的是右值。有些变量既可以当左值又可以当右值。
//进一步来讲，左值为Lvalue，其实L代表Location，表示在内存中可以寻址，可以给它赋值（常量const类型也可以寻址，但是不能赋值），
//Rvalue中的R代表Read，就是可以知道它的值。
//左值符号&和右值符号&&
//左值的声明符号为&，右值的声明符号为&&。在C++中，临时对象不能作为左值，但是可以作为常量引用const &
//{
	double b = 1.2;
	//int& a = b; //错误，因为这种方式将产生一个临时变量，而临时变量具有常性，也就是说a引用的是带有常性的临时变量 
	const int& a = b;//所以需要用const修饰，此时的a是这个临时变量的名字，与b将没有关系，不论怎么修改b，都不会影响a。当然a并不能被修改
//}
void print_lvalue(int& i)
{
	cout << "lvalue:" << i << endl;
}
void print_rvalue(int&& i)
{
	cout << "rvalue:" << i << endl;
}
struct X
{
};
void inner0(const X&)
{
	cout << "inner(const X&)" << endl;
}
void inner0(X&&) { cout << "inner0(X&&)" << endl; }
template<typename T>
void outer0(T&& t) { inner0(forward<T>(t)); }

void CPlusPlus11::lValueRvalue()
{
	stdforward();

	int i = 0;
	print_lvalue(i);
	//print_rvalue(i);  //无法将右值引用绑定到左值
	print_rvalue(10);
	//print_lvalue(1);    //非常量引用的初始值必须为左值
	//如果i变量不在使用了，希望把它的值传递出去，下面std::move就为我们提供了将左值引用转换为右值引用的方法。
	print_rvalue(std::move(i));  

	//无论用左值a还是右值X()做参数来调用std::move函数，
	//该实现都将返回无名的右值引用（右值的一种），符合标准中该函数的定义
	X a;
	X&& b = std::move(a);
	X&& c = std::move(X());

	//无论用左值a还是右值X()做参数来调用带有右值引用参数的函数模板outer，
	//只要在outer函数内使用std::forward函数转发参数，
	//就能保留参数的左右值属性，从而实现了函数模板参数的完美转发
	outer0(a);
	outer0(X());
	inner0(forward<X>(X()));
}
//////////////////////////////////////////////////////////////////////////
//template <typename T> 
//struct Identity
//{
//	typedef T type;
//};
//template <typename T> 
//T&& Forward(typename Identity<T>::type&& t)
//{
//	return (T&&)t;
//}
// Disables template argument deduction from Forward helper
template<class T>
struct Identity
{
	// Map T to type unchanged
	typedef T Type;
};

template<class T>
inline T&& Forward(typename Identity<T>::Type& arg) throw()
{
	// Forward arg, given explicitly specified Type parameter
	return (T&&)arg;
}
void inner(int&,int&)
{
	cout << "inner(int&,int&)" << endl;
}
void inner(int&, const int&) 
{
	cout << "inner(int&, const int&)" << endl;
}
void inner(const int&, int&) {
	cout << "inner(const int&, int&)" << endl;
}
void inner(const int&, const int&) {
	cout << "inner(const int&, const int&)" << endl;
}
template <typename T1, typename T2> 
void outer(T1&& t1, T2&& t2) {
	inner(std::forward<T1>(t1), Forward<T2>(t2));
}

void CPlusPlus11::stdforward()
{
	std::string wcmd;
	//std::getline(std::wcin, wcmd); // TODO: It's blocking...
	wcmd = "000赵宇";
	cout << wcmd << endl;
	int a = 1;
	const int b = 2;
	cout << "Directly calling inner()." << endl;
	inner(a, a);
	inner(b, b);
	inner(3, 3);
	inner(a, b);
	inner(b, a);
	inner(a, 3);
	inner(3, a);
	inner(b, 3);
	inner(3, b);
	cout << endl << "Calling outer()." << endl;
	outer(a, a);
	outer(b, b);
	outer(3, 3);
	outer(a, b);
	outer(b, a);
	outer(a, 3);
	outer(3, a);
	outer(b, 3);
	outer(3, b);
}

void CPlusPlus11::variableArray(unsigned int x, unsigned int y)
{
	const int t = 10;
	int a[t];
}

typedef std::chrono::high_resolution_clock c_t;
using namespace std::chrono;
void CPlusPlus11::stdtime()
{
	auto time1(c_t::now());
	int64_t a = 8e9l;
	cout << "a = " << a << endl;

	static const double PI = std::atan(1.0)*4.0;
	static const double H_PI = std::atan(1.0)*2.0;

	std::wstring audio_layouts = lrReturn();
	//wcout << audio_layouts << endl;

	std::wstring name = audio_layouts;
	std::transform(name.begin(), name.end(), name.begin(), std::tolower);
	//wcout << name << endl;

	system_clock::time_point frame_start_time = (system_clock::time_point)(
		duration_cast<seconds>(system_clock::now().time_since_epoch() + seconds{ 5 }));
	int64_t timeout = (uint64_t)duration_cast<nanoseconds>(
		(frame_start_time).time_since_epoch()).count();
	system_clock::time_point frame_start_time01 = (system_clock::time_point)(
		duration_cast<seconds>(system_clock::now().time_since_epoch() + milliseconds{ 5000 }));
	int64_t timeout01 = (uint64_t)duration_cast<nanoseconds>(
		(frame_start_time01).time_since_epoch()).count();

	cout << " timeout " << timeout << " timeout01 " << timeout01 << " delta " << timeout - timeout01 <<endl;

}

std::wstring CPlusPlus11::lrReturn()
{
	return LR"(
		<audio>
			<channel-layouts>
				<channel-layout name="mono"        type="mono"        num-channels="1" channel-order="FC" />
				<channel-layout name="stereo"      type="stereo"      num-channels="2" channel-order="FL FR" />
			</channel-layouts>			
		</audio>
	)";
}


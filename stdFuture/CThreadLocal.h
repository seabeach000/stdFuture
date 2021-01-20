#pragma once
#include <string>
namespace wwxxgg {
	namespace threadlocal {

		struct call_context
		{
			int video_channel = -1;
			int layer = -1;
			//函数外只能定义全局变量或者对象 ，而不能执行语句及调用函数 。
			//std::cout << " threadId " << std::this_thread::get_id() << std::endl;
			static call_context& for_thread();
			std::wstring         to_string() const;
		};

		class scoped_call_context
		{
			call_context saved_;

			scoped_call_context(const scoped_call_context&) = delete;
			scoped_call_context& operator=(const scoped_call_context&) = delete;

		public:
			scoped_call_context() { saved_ = call_context::for_thread(); }
			~scoped_call_context() { call_context::for_thread() = saved_; }
		};

		class ThreadLocal
		{
		public:
			ThreadLocal();
			virtual ~ThreadLocal();

			void test();
		};

	}
}


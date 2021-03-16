// cpp_standard_lib_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

/**
 * c++路线：标准库
 */
using namespace std;
/**
 * g++编译器基本使用示例 g++ -std=c++14 thread.cpp -o thread -pthread  （手动链接thread库）
 */
#include <algorithm> 
void* doo = nullptr;
/**
 * 自带算法
 */
void test_minmax() {
	//基本比较函数
	cout << "std::min(2011, 2014):\t\t\t ";
	cout << std::min(2011, 2014) << "\n";                           // 2011
	cout << "std::min({3, 1, 2011, 2014, -5}):\t";
	cout << std::min({ 3, 1, 2011, 2014, -5 }) << "\n";               // -5
	//lambda函数定义比较规则，这里取绝对值
	cout << "std::min(-10, -5, [](...) {...}):\t\t";
	cout << std::min(-10, -5, [](int a, int b)
		{ return std::abs(a) < std::abs(b); }) << "\n\n";

	std::pair<int, int> pairInt = std::minmax(2011, 2014);
	auto pairSeq = std::minmax({ 3, 1, 2011, 2014, -5 });
	auto pairAbs = std::minmax({ 3, 1, 2011, 2014, -5 }, [](int a, int b)
		{ return std::abs(a) < std::abs(b); });
	//返回pair
	cout << "pairInt.first, pairInt.second:\t\t";
	cout << pairInt.first << ", " << pairInt.second << "\n"; // 2011,2014
	cout << "pairSeq.first, pairSeq.second:\t\t";
	cout << pairSeq.first << ", " << pairSeq.second << "\n";  // -5,2014
	cout << "pairAbs.first, pairAbs.second:\t\t ";
	cout << pairAbs.first << ", " << pairAbs.second << "\n";  // 1,2014
}
/**
 * move和copy
 * std::move会把尝试把参数转为右值引用，将资源移动；copy性能较低，是整体复制
 * copy可能会因内存不足导致分配空间失败；而move后的源将处于“有效但未指定”状态
 * 如果编译器无法进行move，则会使用copy
 *
 * 移动语义具有两个优点。首先，节约性能，不需要多余的内存分配和释放。其次，存在无法复制的对象，例如线程或锁。
 */
#include <utility>
void test_move_and_copy() {
	std::string str1 = "abcd";
	std::string str2 = "efgh";
	std::cout << "str1: " << str1 << std::endl;
	std::cout << "str2: " << str2 << "\n\n";

	// Copying
	str2 = str1;             // copy semantic
	std::cout << "After copying" << std::endl;
	std::cout << "str1: " << str1 << std::endl;
	std::cout << "str2: " << str2 << "\n\n";

	str1 = "abcd";
	str2 = "efgh";

	// Moving 
	//移动操作后，str1为空。（不能保证，但通常是这样）
	//使用函数std::move明确请求了移动语义。
	//如果确定不再需要移动语义的源，则编译器将自动执行移动语义。
	str2 = std::move(str1);
	std::cout << "After moving" << std::endl;
	std::cout << "str1: " << str1 << std::endl;
	std::cout << "str2: " << str2 << "\n\n";
}
//对于自定义类，需要有对应的构造函数或赋值运算符重载才有对应的语义功能
class MyData {
	MyData(MyData&& m) = default; // move constructor
	MyData& operator = (MyData&& m) = default; // move assignment 
	MyData(const MyData& m) = default; // copy constructor
	MyData& operator = (const MyData& m) = default; // copy assignment
};
/**
 * std::forward
 * 工厂函数是创建对象的函数，因此必须相同地传递参数。
 * 构造函数通常使用其参数来使用相同的参数来初始化其基类。forward是通用库作者的常用工具
 * forward与可变参数模板结合使用可以定义完全通用的函数模板,可以接受任意数量的参数，并以不变的方式转发它
 */
struct MyData_2 {
	MyData_2(int, double, char) {};
};
//函数模板createT必须将其参数用作通用引用：Args&& …args`。通用引用或也称为转发引用是类型推导上下文中的右值引用
template <typename T, typename...  Args>
T createT(Args&&... args) {
	return T(std::forward<Args>(args)...);
}
#include <vector>
#include <initializer_list>
typedef std::vector<int> IntVec;
using std::initializer_list;
void test_forward() {
	int a = createT<int>();
	int b = createT<int>(1);
	std::string s = createT<std::string>("Only for testing.");
	MyData_2 myData = createT<MyData_2>(1, 3.19, 'a');
	IntVec intVec = createT<IntVec>(initializer_list<int>({ 1, 2, 3 }));
}
/**
 * std::swap
 * 使用move语义交换
 */
template <typename T>
inline void swap(T& a, T& b) {
	T tmp(std::move(a));
	a = std::move(b);
	b = std::move(tmp);
}
/**
 * std::bind
 * std::function
 *
 * c++11以后，一般使用lambda表达式直接代替bind，auto自动推导代替function
 *
 * 通过std::bind，可通过多种方式创建函数对象：
 * 将参数绑定到任意位置，
 * 改变参数的顺序，
 * 引入占位符作为参数，
 * 调用新创建的函数对象，在STL的算法中使用它们或将它们存储在std::function中。
 */
#include <functional>
using namespace std::placeholders;
using std::bind;
using std::function;
double divMe(double a, double b) { return a / b; };
void test_bind_and_func() {
	function <double(double, double)> myDiv1 = bind(divMe, _1, _2);
	function <double(double)> myDiv2 = bind(divMe, 2000, _1);
	std::cout << (divMe(2000, 10) == myDiv1(2000, 10) == myDiv2(10));
}
//更多应用
#include <map>
using std::make_pair;
using std::map;
void test_function() {
	//用map做函数映射，可代替switch控制块
	map<const char, std::function<double(double, double)>> tab;
	tab.insert(make_pair('+', [](double a, double b) { return a + b; }));//lambda代替bind
	tab.insert(make_pair('-', [](double a, double b) { return a - b; }));
	tab.insert(make_pair('*', [](double a, double b) { return a * b; }));
	tab.insert(make_pair('/', [](double a, double b) { return a / b; }));

	std::cout << "3.5 + 4.5\t=  " << tab['+'](3.5, 4.5) << "\n";  //3.5 + 4.5	=  8
	std::cout << "3.5 - 4.5\t=  " << tab['-'](3.5, 4.5) << "\n";  //3.5 - 4.5	=  -1
	std::cout << "3.5 * 4.5\t=  " << tab['*'](3.5, 4.5) << "\n";  //3.5 * 4.5	=  15.75
	std::cout << "3.5 / 4.5\t=  " << tab['/'](3.5, 4.5) << "\n";  //3.5 / 4.5	=  0.777778
}
/**
 * std::pair
 * std::make_pair
 * 可构建任意类型对，常用于各种map中
 */
void test_pairs() {
	pair<const char*, double> charDoub("str", 3.14);
	pair<const char*, double> charDoub2 = make_pair("str", 3.14);
	auto charDoub3 = make_pair("str", 3.14);

	cout << charDoub.first << ", " << charDoub.second << "\n";    // str, 3.14
	charDoub.first = "Str";
	get<1>(charDoub) = 4.14;
	cout << charDoub.first << ", " << charDoub.second << "\n";    // Str, 4.14
}
//元组扩展到更多个元素
void test_elements() {
	//tuple是固定大小，泛化的pair
	std::tuple<std::string, int, float> tup1("first", 3, 4.17f);
	auto tup2 = std::make_tuple("second", 4, 1.1);

	int first = 1;
	int second = 2;
	int third = 3;
	int fourth = 4;
	cout << first << " " << second << " "
		<< third << " " << fourth << endl;          // 1 2 3 4

	auto tup = tie(first, second, third, fourth)      // bind the tuple
		= std::make_tuple(101, 102, 103, 104);   // create the tuple 
												 // and assign it
	cout << get<0>(tup) << " " << get<1>(tup) << " " << get<2>(tup)
		<< " " << get<3>(tup) << endl;              // 101 102 103 104
	cout << first << " " << second << " " << third << " "
		<< fourth << endl;                          // 101 102 103 104

	first = 201;
	get<1>(tup) = 202;
	cout << get<0>(tup) << " " << get<1>(tup) << " " << get<2>(tup)
		<< " " << get<3>(tup) << endl;              // 201 202 103 104
	cout << first << " " << second << " " << third << " "
		<< fourth << endl;                          // 201 202 103 104

	int a, b;
	tie(std::ignore, a, std::ignore, b) = tup;
	cout << a << " " << b << endl;                   // 202 104
}
/**
 * std::reference_wrapper
 */
void foo() {
	std::cout << "Invoked" << std::endl;
}
void test_ref_wrap() {
	typedef void callableUnit();
	std::reference_wrapper<callableUnit> refWrap(foo);

	refWrap(); // Invoked
}
/**
 * std::ref		将创建一个非常量引用包装
 * std::cref	将创建一个常量引用包装
 */
void invokeMe(const std::string& s) {
	std::cout << s << ": const " << std::endl;
}
template <typename T>
void doubleMe(T t) {
	t *= 2;
}
void test_ref() {
	std::string s{ "string" };
	invokeMe(std::cref(s));        // string

	int i = 1;
	std::cout << i << std::endl;   // 1
	doubleMe(i);
	std::cout << i << std::endl;   // 1
	doubleMe(std::ref(i));
	std::cout << i << std::endl;   // 2
}
/**
 * 智能指针
 * 根据RAII习惯用法管理其资源。因此，如果智能指针超出范围，资源将自动释放。
 * (RAII:C ++中的一种流行技术，其中资源获取和释放与对象的生存期绑定。
 * 对于智能指针，这意味着内存在构造函数中分配，并在析构函数中释放。当对象超出范围时将调用析构函数。)
 *
 * std::unique_ptr
 * 独占资源，无法拷贝
 *
 * std::shared_ptr
 * 具有共享变量的参考计数器。自动管理参考计数器。如果引用计数器为0，则删除资源。
 *
 * std::weak_ptr
 * 帮助中断std :: shared_ptr的周期。不修改参考计数器。
 *
 */
#include <iomanip>
class MyStruct {
public:
	MyStruct() {
		std::cout << std::setw(15) << std::left << (void*)this << " Hello " << std::endl;
	}
	~MyStruct() {
		std::cout << std::setw(15) << std::left << (void*)this << " Good Bye " << std::endl;
	}
};
void test_unique_ptr() {

	std::unique_ptr<int> uniqInt(new int(2011));
	std::cout << "*uniqInt: " << *uniqInt << std::endl;
	std::cout << std::endl;
	//大括号测试生命周期
	{
		std::unique_ptr<MyStruct[]> myUniqueArray{ new MyStruct[5] };
	}
	std::cout << std::endl;

	{
		std::unique_ptr<MyStruct[]> myUniqueArray{ new MyStruct[1] };
		MyStruct myStruct;
		myUniqueArray[0] = myStruct;
	}
	std::cout << std::endl;

	{
		std::unique_ptr<MyStruct[]> myUniqueArray{ new MyStruct[1] };
		MyStruct myStruct;
		myStruct = myUniqueArray[0];
	}
	std::cout << std::endl;
}
//std::shared_ptr
//有两个句柄：一个用于资源，另一个用于引用计数器。
//通过复制shared_ptr，引用计数将增加一。如果shared_ptr超出范围，则减少1。
//如果引用计数器的值为0，则C++运行时会自动释放资源，因为不再有引用该资源的shared_ptr。
//当最后一个std :: shared_ptr超出范围时，才发生资源释放。 
//C++运行时保证引用计数器的调用是原子操作。由于这种管理，shared_ptr比原始指针或unique_ptr消耗更多的时间和内存。
class ShareMe : public std::enable_shared_from_this<ShareMe> {
public:
	std::shared_ptr<ShareMe> getShared() {
		return shared_from_this();
	}
};
void test_shared_ptr() {
	std::shared_ptr<ShareMe> shareMe(new ShareMe);
	std::shared_ptr<ShareMe> shareMe1 = shareMe->getShared();
	{
		auto shareMe2(shareMe1);
		std::cout << "shareMe.use_count(): " << shareMe.use_count() << std::endl; //3
	}
	std::cout << "shareMe.use_count(): " << shareMe.use_count() << std::endl; //2
	shareMe1.reset();
	std::cout << "shareMe.use_count(): " << shareMe.use_count() << std::endl; //1
}
//std::weak_ptr
void test_weak_ptr() {
	std::cout << std::boolalpha << std::endl;

	auto sharedPtr = std::make_shared<int>(2011);
	std::weak_ptr<int> weakPtr(sharedPtr);
	std::cout << "weakPtr.use_count(): " << weakPtr.use_count() << std::endl;
	std::cout << "sharedPtr.use_count(): " << sharedPtr.use_count() << std::endl;
	std::cout << "weakPtr.expired(): " << weakPtr.expired() << std::endl; //检查是否已删除资源

	if (std::shared_ptr<int> sharedPtr1 = weakPtr.lock()) { //创建一个shared_ptr在资源上
		std::cout << "*sharedPtr: " << *sharedPtr << std::endl;
		std::cout << "sharedPtr1.use_count(): " << sharedPtr1.use_count() << std::endl; //2
	}
	else {
		std::cout << "Don't get the resource!" << std::endl;
	}

	weakPtr.reset();
	if (std::shared_ptr<int> sharedPtr1 = weakPtr.lock()) {
		std::cout << "*sharedPtr: " << *sharedPtr << std::endl;
		std::cout << "sharedPtr1.use_count(): " << sharedPtr1.use_count() << std::endl;
	}
	else {
		std::cout << "Don't get the resource!" << std::endl;
	}
}
//cyclic references
//shared_ptr有可能发生循环引用，可以使用weak_ptr打破
struct Son;
struct Daughter;
struct Mother {
	~Mother() {
		std::cout << "Mother gone" << std::endl;
	}
	void setSon(const std::shared_ptr<Son> s) {
		mySon = s;
	}
	void setDaughter(const std::shared_ptr<Daughter> d) {
		myDaughter = d;
	}
	std::shared_ptr<const Son> mySon;
	std::weak_ptr<const Daughter> myDaughter;//这里用了weak_ptr
};
struct Son {
	Son(std::shared_ptr<Mother> m) :myMother(m) {}
	~Son() {
		std::cout << "Son gone" << std::endl;
	}
	std::shared_ptr<const Mother> myMother;
};
struct Daughter {
	Daughter(std::shared_ptr<Mother> m) :myMother(m) {}
	~Daughter() {
		std::cout << "Daughter gone" << std::endl;
	}
	std::shared_ptr<const Mother> myMother;
};
void test_cycle_ref() {
	std::cout << std::endl;
	{
		std::shared_ptr<Mother> mother = std::shared_ptr<Mother>(new Mother);
		std::shared_ptr<Son> son = std::shared_ptr<Son>(new Son(mother));
		std::shared_ptr<Daughter> daughter = std::shared_ptr<Daughter>(new Daughter(mother));
		mother->setSon(son);
		mother->setDaughter(daughter);
	}
	std::cout << std::endl;
	//最终结果只输出了daughter的析构函数，因为mother和son发生了循环引用，而同样写法的daughter由于用了weak_ptr产生了不同的结果
}
//对比测试性能
#include <chrono>
#include <memory>
static const long long numInt = 100000000;
void test_ptrs() {
	auto start = std::chrono::system_clock::now();
	for (long long i = 0; i < numInt; ++i) {
		//int* tmp(new int(i));											//2s+
		//delete tmp;
		// std::shared_ptr<int> tmp(new int(i));						//12s+
		// std::shared_ptr<int> tmp(std::make_shared<int>(i));			//28s+
		// std::unique_ptr<int> tmp(new int(i));						//7s+
		//std::unique_ptr<int> tmp(std::make_unique<int>(i));			//8s+
	}
	std::chrono::duration<double> dur = std::chrono::system_clock::now() - start;
	std::cout << "time make_unique: " << dur.count() << " seconds" << std::endl;
}
//传递智能指针的几条规则
//R.32：取一个unique_ptr<widget>参数来表示一个函数假定了一个小部件的所有权
struct Widget {
	Widget(int) {}
};
void sink(std::unique_ptr<Widget> uniqPtr) {
	// do something with uniqPtr
}
void test_R32() {
	auto uniqPtr = std::make_unique<Widget>(1998);

	sink(std::move(uniqPtr));      // (1)
	//sink(uniqPtr);                 // (2) ERROR
}
//R.33: Take a unique_ptr<widget>& parameter to express that a function reseats the widget.
void reseat(std::unique_ptr<Widget>& uniqPtr) {
	uniqPtr.reset(new Widget(2003));   // (0)
	// do something with uniqPtr
}
void test_R33() {
	auto uniqPtr = std::make_unique<Widget>(1998);

	//reseat(std::move(uniqPtr));       // (1) ERROR
	reseat(uniqPtr);                  // (2) 
}
//R.34: Take a shared_ptr<widget> parameter to express that a function is part owner.
//R.35: Take a shared_ptr<widget>&parameter to express that a function might reseat the shared pointer.
//R.36 : Take a const shared_ptr<widget>&parameter to express that it might retain a reference count to the object.
void share(std::shared_ptr<Widget> shaWid);//在函数正文的生存期内，此方法是Widget的共享所有者。在功能主体开始时，我们将增加参考计数器；在函数结束时，我们将减少参考计数器；因此，只要我们使用它，小部件就会保持活动状态。
void reset(std::shared_ptr<Widget>& shadWid);//此函数不是窗口小部件的共享所有者，因为我们不会更改参考计数器。我们无法保证Widget在函数执行期间会保持活动状态，但是我们可以重新放置资源。非常量左值引用更像是借用了具有重新安置能力的资源。
void mayShare(const std::shared_ptr<Widget>& shaWid);//此函数仅借用资源。我们既不能延长资源的寿命，也不能重新安置资源。老实说，我们应该改用指针（Widget *）或引用（Widget＆）作为参数，因为使用std :: shared_ptr不会增加任何价值。
//R.37: Do not pass a pointer or reference obtained from an aliased smart pointer.
void oldFunc(Widget wid) {
	// do something with wid
}
void shared(std::shared_ptr<Widget>& shaPtr) {       // (2)通过引用传递参数，则不会增加引用计数
	auto keepAlive = shaPtr;//增加引用计数，保证在oldFunc中的可用性（就像在使用asio写网络服务时时，经常需要auto self(shared_from_this());让lambda表达式捕获self）
	oldFunc(*shaPtr);                                // (3)由于没有增加引用计数，无法保证传递过去的参数有效；解决方案是拷贝，保证引用计数增加、或者在传参时拷贝
	// do something with shaPtr
}
auto globShared = std::make_shared<Widget>(2011);   // (1)全局共享指针
void test_R37() {
	shared(globShared);
}


int main()
{
	test_bind_and_func();
}

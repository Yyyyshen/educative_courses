// cpp_templates_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;
/**
 * c++路线：
 * 模板
 */
void* foo = nullptr;
//关于constexpr
const int func() {
	return 10;//const 只表示值无法被直接修改，并不能表示就是常量
}
constexpr int func_constexpr() {
	return 10;
}
void test_constexpr() {
	//int arr[func()];//compile error
	int arr[func_constexpr()];
}
//模板函数
template<typename T>
void f(T s)
{
	std::cout << s << '\n';
}
//重载模板
template void f<double>(double); // instantiates f<double>(double)
template void f<>(char); // instantiates f<char>(char), template argument deduced
template void f(int); // instantiates f<int>(int), template argument deduced
//模板应用
template<int m, int n>
struct Power {
	static int const value = m * Power<m, n - 1>::value;
};

template<int m>
struct Power<m, 0> {
	static int const value = 1;
};
void test_template() {
	std::cout << Power<2, 10>::value << std::endl;
}
//模板类
template <typename T>
struct Base {
	void func_base() { cout << "Base" << endl; }
};
template <typename T>
struct Derived : Base<T> {
	using Base<T>::func_base;
	void func_derived() {
		//func_base();       // ERROR 模板类继承，子类不会自动提供基类方法
		//需要使用基类方法可以这样
		this->func_base();
		Base<T>::func_base();
		func_base();//加入using声明后，可直接使用
	}
};
void test_template_1() {
	Derived<int> d;
	d.func_derived();
}
//别名模板
template <typename T, int Line, int Col> 
class Matrix {
};
template <typename T, int Line>
using Square = Matrix<T, Line, Line>;
template <typename T, int Line>
using Vector = Matrix<T, Line, 1>;
Matrix<int, 5, 3> ma;
Square<double, 4> sq;
Vector<char, 5> vec;
//各参数类型模板
template <typename T>
class ClassTemplate {
public:
	ClassTemplate() {
		std::cout << "typeid(T).name(): " << typeid(T).name() << std::endl;
	}
};
template < void(*func)(void) >
class AcceptFunction {
public:
	AcceptFunction() {
		std::cout << "AcceptFunction: " << typeid(func).name() << std::endl;
	}
};
void test_template_2() {
	ClassTemplate<int> clTempInt;
	ClassTemplate<double> clTempDouble;
	ClassTemplate<std::string> clTempString;
	AcceptFunction<test_template> tempFunc;
}
//模板模板
#include <initializer_list>
#include <list>
#include <vector>
template <typename T, template <typename, typename> class Cont >
class Matrix_TT {
public:
	explicit Matrix_TT(std::initializer_list<T> inList) : data(inList) {
		for (auto d : data) std::cout << d << " ";
	}
	int getSize() const {
		return data.size();
	}

private:
	Cont<T, std::allocator<T>> data;//可使用相同签名的容器类型，如vector、list等
};
void test_template_3() {
	Matrix_TT<int, std::vector> myIntVec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	std::cout << std::endl;
	std::cout << "myIntVec.getSize(): " << myIntVec.getSize() << std::endl;
}
//模板参数；默认类型
template <typename T, typename Pred = std::less<T>>
bool isSmaller(T fir, T sec, Pred pred = Pred()) {
	return pred(fir, sec);
}
template <typename R, typename T, typename U>
R add(T fir, U sec) {
	return fir + sec;
}
//模板专业化
class Account {};
template<typename T>
struct Type {
	std::string getName() const {
		return "unknown";
	}
};
template<typename T>
struct Type<T*> {
	std::string getName() const {
		return "pointer";
	}
};
template<typename T>
struct Type<const T> {
	std::string getName() const {
		return "const";
	}
};
template<>
struct Type<int> {
	std::string getName() const {
		return "int";
	}
};
template<>
struct Type<double> {
	std::string getName() const {
		return "double";
	}
};
template<>
struct Type<std::string> {
	std::string getName() const {
		return "std::string";
	}
};
template<>
struct Type<Account> {
	std::string getName() const {
		return "Account";
	}
};



int main()
{
	test_template_2();
}

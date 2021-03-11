// cpp_oop_01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
using namespace std;
/**
 * c++路线
 * 2.面向对象
 */
class Account {
public:
	//包含各种类特性的例子
	Account() = default;
	Account(int numb) : numberOf(numb), deposits(new double[numb]) {}

	Account(const Account& other) : numberOf(other.numberOf), deposits(new double[other.numberOf]) {
		std::copy(other.deposits, other.deposits + other.numberOf, deposits);
	}
	//重载操作符
	Account& operator = (const Account& other) {
		numberOf = other.numberOf;
		deposits = new double[other.numberOf];
		std::copy(other.deposits, other.deposits + other.numberOf, deposits);
		return *this;
	}

	Account(Account&& other) noexcept :numberOf(other.numberOf), deposits(other.deposits) {
		other.deposits = nullptr;
		other.numberOf = 0;
	}
	//右值引用赋值
	Account& operator =(Account&& other) noexcept {
		numberOf = other.numberOf;
		deposits = other.deposits;
		other.deposits = nullptr;
		other.numberOf = 0;
		return *this;
	}

	~Account() {
		if (deposits != nullptr)
		{
			delete[] deposits;
			deposits = nullptr;
		}
	}

	//数据封装
	int getNumberOf() {
		return numberOf;
	}

	double* getDeposits() {
		return deposits;
	}

	virtual void withdraw(double amt) {
		balance -= amt;
	}

private:
	int numberOf;
	double* deposits;
protected:
	double balance;
};

class A {};
class B {};
//显式重载换算运算符
class MyClass {
public:
	MyClass() {}
	explicit MyClass(A) {}                // since C++98
	explicit operator B() { return B(); }   // new with C++11
};

//继承
// Base class 
class Base {

public:
	Base() {
		cout << "Base class default constructor!" << endl;
	}
	// Base class's parameterised constructor     
	Base(float i) {
		cout << "Base class parameterized constructor" << endl;
	}
	~Base() {
		cout << endl << "Base class Destructor!";
	}
};
// Derived class 
class Derived : public Base {
public:
	Derived() {
		cout << "Derived class default constructor!" << endl;
	}

	// Derived class's parameterised constructor 
	Derived(float num) : Base(num) {
		cout << "Derived class parameterized constructor" << endl;
	}
	~Derived() {
		cout << endl << "Derived class Destructor!";
	}
};

void test_inheritance() {
	Derived obj;
	//构造顺序：基类->子类
	//销毁顺序：子类->基类

	/*
	通过使用私有继承，在派生类和main中无法访问基类的私有数据成员和成员函数。基类的受保护成员和公共成员可被派生类访问，但不能从主类访问。
	通过使用受保护的继承，无法在派生类和main中访问基类的私有成员。基类的受保护成员和公共成员可被派生类访问，但不能从主类访问。
	通过使用公共继承，无法在派生类和main中访问基类的私有成员。基类的受保护成员可被派生类访问，但不能在main中访问。基类的公共成员可从派生类和主要对象访问。
	*/
}
//多继承
class Vehicle {};
class Cars {};
class Honda : public Vehicle, public Cars {};
//多级继承
class parent {}；;
class child : public parent {};
class grandChild : public child {};

//虚函数
class BankAccount : public Account {
	virtual void withdraw(double amt) {
		if ((balance - amt) > 0.0) balance -= amt;
	}
};
/*
多态：

在运行时选择该方法。

这通常称为动态绑定或后期绑定。

规则：

构造函数不能是虚拟的。

虚方法不必被覆盖。

声明为虚拟的方法在层次结构中保持虚拟状态。

重写方法中的参数必须与虚拟方法中的参数相同。

说明符虚拟是获得多态行为所必需的。

私有方法可以在基类中重写。

虚拟析构函数

通过指针或对基类的引用破坏对象时，析构函数必须是虚拟的。

虚拟基类

虚拟基类解决了多重继承的问题，因为派生类仅获得一个基类。当一个类实际上是从基类派生的时，它将成为一个虚拟基类。

*/
// A simple Shape interface which provides a method to get the Shape's area
class Shape {
public:
	virtual float getArea() { return 0; }//声明为虚函数，否则还是会调用基类的方法
	//virtual float getArea() = 0;//纯虚函数
};

// A Rectangle is a Shape with a specific width and height
class Rectangle : public Shape {   // derived form Shape class
private:
	float width;
	float height;

public:
	Rectangle(float wid, float heigh) {
		width = wid;
		height = heigh;
	}
	float getArea() {
		return width * height;
	}
};

// A Circle is a Shape with a specific radius
class Circle : public Shape {
private:
	float radius;

public:
	Circle(float rad) {
		radius = rad;
	}
	float getArea() {
		return 3.14159f * radius * radius;
	}
};

void test_polymorphism() {
	Rectangle r(2, 6);    // Creating Rectangle object
	Shape* shape = &r;   // Referencing Shape class to Rectangle object
	//如果不是虚函数，会输出0
	cout << "Calling Rectangle from shape pointer: " << shape->getArea() << endl; // Calls shape's dynamic-type's

	Circle c(5);    // Creating Circle object
	shape = &c;   // Referencing Shape class to Circle object

	cout << "Calling Circle from shape pointer: " << shape->getArea() << endl;

}
//纯虚拟类
class Foo {
public:
	virtual void foo() = 0;
};
void test_foo() {
	//Foo f;	//纯虚拟类不能构造对象
	Foo* pf;
}

int main()
{
	test_polymorphism();
}

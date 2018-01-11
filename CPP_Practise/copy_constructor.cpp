#include<iostream>
using namespace std;

/*
合成拷贝构造函数： 如果类没有显示定义构造函数，编译器就会自动生成，合成拷贝构造函数（默认的拷贝构造函数），其实就是构造函数的重载。默认的拷贝构造函数是浅拷贝。
浅拷贝（位拷贝）：原对象的内存复制给新的对象，包括里面的指针（资源内存地址）
深拷贝（值拷贝）：如果一个类拥有资源，当这个类的对象发生复制过程的时候，资源重新分配

浅拷贝(影子克隆):只复制对象的基本类型,对象类型,仍属于原来的引用.
深拷贝(深度克隆):不仅复制对象的基本类,同时也复制原对象中的对象.就是说完全是新对象产生的

拷贝构造函数
以下情况都会调用拷贝构造函数：

　　1、一个对象以值传递的方式传入函数体
　　2、一个对象以值传递的方式从函数返回
　　3、一个对象需要通过另外一个对象进行初始化。

移动构造函数
派生类析构函数值负责释放派生类自己分配的资源

类的6个默认函数：
1. 构造函数
2. 拷贝函数：参数必须是引用&，不能是值传递，否则会引发无穷递归。可以有多个参数，但是第一个必须是被类的引用类型，且其他参数都必须有默认值
3. 析构函数
4. 赋值运算符重载，A&operator = (const A&)
5. 取地址运算符重载
6. const修饰的取地址运算符重载

*/


class A {
public:
	int sz;

	A(int size): sz(size) { 
		s = new string(sz,'A');
	    cout <<"A::A(int size)"<<endl;
	}
	//A(const A &a) sz(a.sz){s=a.s;} //默认的拷贝构造函数
	#if 1//自定义的拷贝构造函数
    A(const A &a) : sz(a.sz){
    	s = new string(a.sz,'B');
    	cout << "copy constructor" << endl;
    } 
    #endif
	~A() {
		cout <<"A::~A()"<<endl;
		delete s;
	}
	void print() {cout << "*s add = " << *s << ", s add= "<< s <<endl;}
	//A* operator &(){return this;} //默认的取地址运算符重载
	//const A * operator& () const{return this;} //默认的取地址运算符重载
	//A&operator = (const A&) {return *this;} //默认的是赋值运算符重载
private:
	string *s;	
};

int main() {

	{
		A a1(10);
		cout << "a1 add: "<< &a1 << endl;
		a1.print();

		A a2 = a1;//调用的也是默认拷贝构造函数？对象a2不存在，所以是调用拷贝A的调用拷贝构造函数并用a1初始化出来的
		cout << "a2 add: "<< &a2 << endl;
		a2.print();

		A a3(a2);//调用的是默认拷贝构造函数
		cout << "a3 add: "<< &a3 << endl;
		a3.print();
		//a1 = a2;
		//cout << "a1 add: "<<  a1 << endl;
		//a1->print();
		//cout << "a2 add: "<<  a2 << endl;
		//a2->print();		
		//delete a1;
		//delete a2;
	}
	return 0;
}
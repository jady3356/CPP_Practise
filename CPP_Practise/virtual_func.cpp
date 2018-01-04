#include <iostream>

using namespace std;

/*
面向对象（OOP）：
	1）数据抽象 ：类的接口与实现分离
	2）继承 ：定义相似的类并对其相似关系建模
	3）动态绑定：在一定程度上忽略相似类型的区别，而以统一的方式使用它们的的对象

			虚函数：
		    派生类向基类的类型转换： 只能将派生类转化成基类，因为这样基类不可能访问派生类成员，反之不行；
		    					   派生类到基类的转化只能是引用或者指针时才可以。
		    派生类与静态成员:派生类不能访问基类的private成员，只能访问public和protected
		    派生类的构造函数：派生类构造函数并不能直接初始化基类成员，必需通过基类的构造函数来初始化
 
		    overload(重载)：用于同一个类中，参数和返回值都可以重载，但是参数相同且返回值不同的重载是不允许的；相当于函数名称不变单改变了接口
		    override(覆盖)：在子类中，不改变函数参数和返回值，但是改写行为；也是一种多态表现.
		    hide: 在派生类中定义与基类重名的函数。派生类中的重名函数并不会重载基类的函数，只要名字一样就会隐藏，形参列表不一致仍被隐藏

		    虚函数：
					（1）派生类中虚函数的参数和返回值必须和基类一模一样，可以用override关键字让编译器检查这种保证
		    		（2）基类中的虚函数在派生类中也是虚函数，但是关键字可省

*/

class A {
	int i;
public:
	A(int initial): i(initial) {cout << "A constructor..." << endl;}
	void print() { cout << "A private i = " << i  <<endl;}
	virtual void baseFunc() { cout << "A::baseFunc()  "  << endl;} //virtual关键字可以省？No,只是子类的关键字virtual可省

	void baseFuncA(int a) {cout << "A::baseFuncA(int a), a = " << a << endl;}
	//void baseFuncA(char a) {cout << "A::baseFuncA(char a), a = " << a << endl;}
	void baseFuncA(int a, char c) {cout << "A::baseFuncA(int a, char c), a = " << a <<", c = " << c  << endl;}//baseFunc的重载overload
};

class B: public A {
public:
	B(int initial): A(initial) {cout << "B constructor..." << endl;}//派生类构造函数并不能直接初始化基类成员，必需通过基类的构造函数来初始化
    void baseFunc() override { cout << "B::baseFunc() "  << endl; // 如果要搞多态，基类和派生类中的虚函数的参数必须一模一样（参数个数和参数类型）
    //cout << i << endl;派生类不能访问基类的private成员i，只能访问public和protected
    //print();
    }//貌似就是类似重载了这个函数？如果这里的baseFunc的参数与基类A中的不同，那就不是多态了，只是override，并不是动态绑定
    
    //void baseFunc(int i) { cout << "B::baseFunc(int i), override  "  << endl;} //这是一个新的函数跟虚函数baseFunc()没有关系
    //绝对不要重新定义继承而来的非虚(non-virtual)函数,下面只是示例
    void baseFuncA(int a) {cout << "B::baseFuncA(int a), a = " << a << endl;}//覆盖A中的baseFuncA(int)，且是静态的；隐藏A中的baseFuncA(int)和baseFuncA(int a, char c)
    void baseFuncA(char a) {cout << "B::baseFuncA(char a), a = " << a << endl;}//A中同名函数没有这个类型的入参，所以这是一个新的函数；隐藏A中的baseFuncA(int)和baseFuncA(int a, char c)
};


void func(A &a, int j, char s)//多态性表现在函数baseFunc（）上，如果传入A则调A的，如果传入B则调B的。func以统一的方式访问A和B类型的对象
{
	a.print();
	a.baseFunc();
	a.baseFuncA(j);
	a.baseFuncA(s);//为什么没有调用baseFuncA(char)？因为baseFunc并不是虚函数，而且传入的B类型的参数也将转化成A型，所以只能调用A中的baseFuncA(int)
	a.baseFuncA(j,s);
}

int main() {
	A testA(1);// = new A;
	B testB(2);// = new B;
	cout << "sizeof(A) = "<< sizeof(A) << " testA add: "  << &testB <<endl;
	cout << "sizeof(B) = "<< sizeof(B) << " testB add: "  << &testA <<endl;
	func(testA, 3,'A');
	func(testB, 4,'B');

	testA.baseFunc();
	testA.baseFuncA(5);
	testA.baseFuncA(5,'a');

	testB.baseFunc();
	testB.baseFuncA(6);//这里仍然直接调用baseFuncA(char a)，不会调用基类的baseFuncA(int a) ，A中的被隐藏
	testB.baseFuncA('b');
	//testB.baseFuncA(7，'c'); 这里会报错，B的对象并不能直接访问A的成员函数？

	A *ca = &testB;//将派生类转化成基类
	ca->baseFuncA(7,'c');
	ca->print();
}
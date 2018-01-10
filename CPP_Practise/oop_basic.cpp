#include <iostream>
using namespace std;

/*
********************OOP的一些基础知识 start***************************
protected 和 friend： 
        (1)在派生类中，派生类对象可以访问基类的保护成员，基类对象无法访问基类的保护成员;
        (2)在派生类中，可以访问基类的protected和public的成员的；
        (3)在派生类之外，派生类的对象在不能访问基类的protected成员。

	派生类成员不能访问基类的private成员
	派生类访问说明符： 控制派生类用户对基类成员的访问权限
					 对派生类成员访问基类成员的控制没有影响

    类的设计：
    	接口：定义为public
    	供派生类的对象使用：protected（使用场景？：不暴露为公有的接口，可以被派生类使用）
    	供基类和基类友元访问： private

    友元与继承：
        友元关系不能继承

    派生类中的using:
        public: 类的所有用户都能访问
        private: 类的成员和友元访问
        protected： 成员，友元和派生类访问
********************OOP的一些基础知识 end***************************
*/

class A {
public:
    A() { i = 100;cout << "A::A()"<< endl;}
protected:
    int i;
private:
    int j;
};

class B : public A {
public:
    B() {cout << "B::B()"<< endl;}
    void print() {cout << i << endl;}//派生类可以访问基类的protected和public成员
    //void print(A& a) {cout << "B::pirnt(), a.i="<<a.i<< endl;}//报错，派生类对基类A的对象中的protected成员i没有访问权限
                                                                //如果这里派生类中A的对象a可以访问i,那么A中的protected也就失效了
    void print(B& a) {cout << "B::pirnt(), a.i="<<a.i<< endl;} //可以通过派生类B的对象来访问A中的i
};


class C {
public:
    int i;
    C() {i = 101;cout << "A::A()"<< endl;}
};

class D : protected C {//protected并不影响派生类D对i的访问
public:
    D() {cout << "D::D()"<< endl;}
    void pirnt(C& c) {cout << "D::pirnt(), c.i="<<c.i<< endl;}//protected继承并不影响派生类D对C的成员的访问权限

};

int main() {
	B b;
    //cout << b.i << endl;//B的对象不能访问父类的protected成员,派生类之外的派生类的对象在不能访问基类的protected成员
    b.print();
    b.print(b);// 但是B的对象可以,在派生类中，派生类对象可以访问基类的保护成员

    D d;
    //cout << "d.i= "<<d.i<< endl;//报错，因为D是C的protected的继承，所以i变成了protected不可通过D的对象直接访问

}
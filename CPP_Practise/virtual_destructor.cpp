#include<iostream>
using namespace std;

/*
虚析构函数
作用： delete一个指向子类的基类指针时，使得子类的析构函数能被调用
*/

class Abase {
public:
	int i;
	Abase() {i= 100;cout << "A::A()" << endl;}
	virtual ~Abase() {cout << "A::~A()"<< endl;}//如果是虚析构，在deleteA类型的子类B的指针时，那么这个析构的虚函数表指向B的析构函数~B（）
};

class Bd : public Abase {
public:
	~Bd() {cout << "Bd::~Bd()"<< endl;}//Abase中的虚析构函数的虚函数变指向~Bd()
};

class Cd: public Bd {
public:
	~Cd() {cout << "Cd::~Cd()"<< endl;}
};

int main() {

	Abase* a = new Bd;
	delete a;//如果~A()没virtual不是虚函数，将调用A的虚函数，B中的内存将不被释放

	Bd* b = new Bd;
	delete b;

	Bd* c = new Cd;
	delete c;

}
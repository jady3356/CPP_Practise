#include <iostream>
using namespace std;
/*
const: 1. const和引用， 2. const全局常量 3.const和指针
auto: 1. 普通的类型推导 2. 表达式的类型推导
decltype： 1. 普通 2. 表达式 3.和引用
typedef： 只是取别名
*/

extern const int bufsize = 1024; //全局的const在定义时最好也用上extern,这样bufsize就可以在多个文件唯一

class simple {
private:
	int i;
	double d;
public:
	simple() { i = 0; }
	int add(){
		i++;
	}
	void print(){
		cout << "i = " << i << endl;
	}
};

int main() {
	int i;
	const int &a = i;
	//a = 100; // 非法, 因为a是const的引用.也就是说不能改变i的值
	cout << "a = "<< a << endl;

	double b = 1.2345;
	const int &cb = b; // 这个是合法的,cb的值为1, 因为b的临时常量量绑定给cb.这个时候cb是const的所以后面不能改变b的值
	//int &b2 = b; //这个是非法的, 引用的类型和初始化的b的类型不一样, 这个时候cb2是可以改变b的值,所以认为非法
	int b2 = 3;
	const int &cb2 = b2;
	//int &cb3 = cb2;非法, cb3不是const的就可能会改变const的cb2的值,所以非法
	cout <<"cb2 = " << cb2 << endl;

	typedef double db; //给double基础类型取别名
	db dbtest =  3.1415926;
	cout << "dbtest = " << dbtest << endl;

	typedef simple sa; //给自定义simple类取别名
	sa satest;
	satest.add();
	satest.print();

	typedef char* cp;//也可以是指针的取别名
	char c = 'c';
	cp cptest = &c;
	cout << "cp = "<< cptest << endl;

	using SI = simple;//跟typedef一样取别名
	SI SItest;
	SItest.add();
	SItest.print();

	int deci = 0, &decref = deci, *decp = &deci, testdec = 1;
	decltype(deci) deca;//deca为int
	decltype(decref) decb = testdec;//decb 为int&
	decltype(decp) decc = &testdec;//decc为int*
	*decc = 5;
	cout <<"deca = " << deca <<", decb = " << decb << ", decc = " << *decc << endl;
	decltype((deci)) decd = testdec;//decd为int&,双括号之后必为引用
	testdec++;
	cout <<"decd = " << decd <<", decb = " << decb << ", decc = " << decc << endl;
	decltype(*decp) dece = testdec; //dece为int&, 为什么这个时候decc是引用类型? 因为*decp是解引用操作
}
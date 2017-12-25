#include <iostream>
#include <memory>

using namespace std;

struct A {
	int i;
	~A() {cout << "destructor A"<< endl;}
	shared_ptr<A> pre;
	//weak_ptr<A> cur;
	shared_ptr<A> cur;
};

class C;
class B
{
public:
	~B() {cout << "destructor B"<< endl;}
	shared_ptr<C> c_ptr; 
};

class C{
public:
	~C() {cout << "destructor C"<< endl;}
	//shared_ptr<B> b_ptr; 
	weak_ptr<B> b_ptr;
};
 
int main() {
	shared_ptr<A> a1(new A);
	shared_ptr<A> a2(new A);
	a1->pre = a2;
	a2->cur = a1;
	cout << a1.use_count() <<endl;
	cout << a2.use_count() <<endl;
	//a1和a2的use count都为2, 直到main函数结束他们的count都是2，对象无法没销毁，无法调用析构函数，最终导致内存泄露

	//另外一个例子
	shared_ptr<B> Bt(new B);
	shared_ptr<C> Ct(new C);
	Bt->c_ptr = Ct;
	Ct->b_ptr = Bt;
	return 0;
}
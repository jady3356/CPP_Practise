#include <iostream>
#include <vector>
#include <memory>

using namespace std;

/*
智能指针也是模板
对象是电视机，智能ptr是观众
shared_ptr: 可以多个观众共享，没有人看（引用）的时候自动释放。电视归大家所有，没有人看电视的时候就会关掉电视。
		    需要注意的问题： 
		  （1）循环引用导致内存泄露；
		  （2）多线程写
unique_ptr: 只能一个观众独享，其他人都没有权利看。release和reset用法
weak_ptr：不能控制所指对象的生存周期的智能指针，它指向shared_ptr管理的对象。不改变use_count，是在weak_count为0或者超期后释放。
		  主要应用场景是，在使用shared_ptr指向的对象前检查是否还存在,通过lock()来获取被shared_ptr的地址。还有一个用途是解决了多个对象内部含有shared_ptr循环指向，导致对象无法释放的问题

make_shared:
make_unique:
scoped_ptr:与auto_ptr类似，但是scoped_ptr把拷贝构造函数和赋值函数都声明为私有的，拒绝了指针所有权的转让，只有scoped_ptr自己能够管理指针，其他任何人都无权访问被管理的指针，从而保证了指针的绝对安全。 
auto_ptr： (1) 不需要显示的取delete，出栈后自动释放.已经被废弃！！！用unique_ptr替代;
		   (2) 在赋值和作为函数入参时都会丢失所有权
		   (3) 不能让两个auto_ptr指向同一个对象，这样会导致2个auto_ptr共享所有权

Linux 内存管理： 
	64 位系统， 虚拟地址总共2^48 = 256T
	用户空间: 0x0000 7fff ffff ffff - 0x0000 0000 0000 0000  47到63位都为0，表示为用户空间,128T
	内核空间: 0xffff 8000 0000 0000 - 0xffff ffff ffff ffff  128T
	32位系统， 2^32 = 4G
	用户空间: 0xbfff ffff - 0x0000 0000   3G
	内核空间: 0xc000 0000 - 0xffff ffff   1G
*/

class A {
private:
	int i;
public:
	A(int input): i(input) { cout << "A construtor" << endl;}
	~A() {cout << "A De-construtor" << endl;}
	void print() {cout <<" i= " << i << endl;}
};

int main() {
    shared_ptr<int> sp0(new int(42));//跟普通的指针一样，在使用之前一定要初始化，如果shared_ptr<int> sp0；之后就使用会crash
    //与shared_ptr<int> sp0 = make_shared<int> (42)一样
	cout << "*sp0 = " << *sp0  <<" ,sp0 add = " <<  sp0 << " ,sizeof(sp0)= "  << sizeof(sp0)  <<" ,sp0 use_count: " <<  sp0.use_count() << endl;
    //为什么智能指针sp0的大小为16bytes呢？contianed_ptr 和 reference count两个私有变量
	shared_ptr<string> sp1 = make_shared<string> (10, '9');//10个‘A’的字符串
	cout <<"*sp1 = " << *sp1  << ", sp1 add=" <<  sp1 <<", sp1 use_count: " <<  sp1.use_count() << endl;// sp1 什么时候释放呢？

	//{
		auto p = make_shared<string> (10,'A');
		cout << "*p = " << *p <<", p add = "<< p << ", p use_count: " << p.use_count() << endl;
		auto r = make_shared<string> (8,'B');
		cout << "*r = " << *r << ", r add = "<< r << ", r use_count: " << r.use_count() << endl;
		auto q(p);// p.use_count = 3
		cout << "*q = " << *q << ", q add = "<< q << ", p use_count: " << p.use_count() << endl;
		r = q; //指针r存储的对象的内存被释放，因为r原来指向的对象没有人用了，r.use_count为0
		cout << "p use_count: " << p.use_count() << endl;

		shared_ptr<string> x = make_shared<string> (8, 'C');//x指向的对象的地址为原来r中对象的地址，因为r的地址已经释放了，可重用了
		cout << "*x = " << *x << ", x add = "<< x << " ,x use_count: " << x.use_count() <<", p use_count = " << p.use_count() << endl;
		p = x;//x的引用+1， x.use_count = 2, p的引用-1
		cout << "*x = " << *x << ", x add = "<< x << " ,x use_count: " << x.use_count() << endl;

		shared_ptr<string> y = make_shared<string> (8, 'D');
		cout << "*y = " << *y <<", y add = "<< y << ", y use_count: " << y.use_count() << endl;
		x = y;//y的引用+1，y.use_count = 2， x的引用-1
		cout << "*y = " << *y <<", y add = "<< y << ", y use_count: " << y.use_count() << endl;

	//}

	A* a1 = new A(1);
	cout << "a1 add=" << a1 << " size= "<< sizeof(A) << endl;
	a1->print();
	delete a1;
	a1 = NULL;
	//cout << "a1 add=" << a1 << endl;

	shared_ptr<A> sp2(new A(2));//必须直接初始化，不能写成shared_ptr<A> sp2 = new A(2)
	sp2->print();
	cout << "sizeof(sp2)=" << sizeof(sp2) <<" sp2 add= " << sp2 << " sp2 use_count: " <<  sp2.use_count()<< endl;
	auto a2 = sp2;
	a2->print();
	cout << "a2 add= "<<a2 << ", sp2 use_count: " << sp2.use_count() << endl;
	a2 = NULL;
	cout <<"sp2 add= " << sp2 << ", sp2 use_count: " << sp2.use_count() << endl;
	//delete sp2;//报错，不能释放智能指针？因为sp2是一个指向智能指针的栈内存地址，它并不是一个普通的new出来的堆的ptr

    weak_ptr<A> wp(sp2);// wp并不能直接访问shared_ptr里面的对象
    cout << "sp2 use count= " << sp2.use_count() << endl;// sp2的use count为1， weak 为1
    if(shared_ptr<A> np = wp.lock()) // 通过lock连来检查shared_ptr是否还存在，如果expired()为TRUE则返回，空的shared_ptr；如果为FALSE则返回shared_ptr
    	cout << "sp2 add=" << sp2 << ", sp2 use count= " << sp2.use_count() <<", np add: " << np << ", wp lock = " << wp.lock() << endl;
    	//这个时候use count临时为2和weak=1？因为被np用了？
    //np->print();np已经out of scope了！！！if后面有大括号。。。
    cout << "sp2 use count= " << sp2.use_count() << endl;// sp2的use count为1， weak 为1

    weak_ptr<A> wp1(a2);// wp并不能直接访问shared_ptr里面的对象
    if(shared_ptr<A> np1 = wp1.lock()) //a2为Null, lock的返回值应该也为null
    	cout << "a2 add=" <<  a2 << ", a2 use count= " << a2.use_count() <<", np1 add: " << np1 << ", wp lock = " << wp.lock() << endl;

    weak_ptr<A> wp2;// wp并不能直接访问shared_ptr里面的对象
    wp2 = sp2; //sp2的weak 变为2， use count仍为1
    cout << "sp2 use count= " << sp2.use_count() << endl;
    if(auto np2 = wp2.lock()) //这里必须先用lock得到shared_ptr赋值给np2，然后再用
        np2->print();

    auto_ptr<A> ap(new A(3));
    ap->print();
    cout << "ap get() = " << ap.get() << endl;
	ap.reset(new A(4));//释放之前申请的A（3）， 重新分配A（4）
	cout << "ap get() = " << ap.get() << endl;
	ap->print();
    A *aa = ap.release();//release返回地址并放弃控制权，表示ap不再是一个auto_ptr了，需要用delete aa
    cout << "aa add = " << aa << endl;
    delete aa;

    unique_ptr<A> up(new A(5));
    cout << "up get() = " << up.get() << endl;
    //auto up1 = up; unique_ptr不能赋值，因为它对对象的所有权唯一
    unique_ptr<A> up1(up.release());// release放弃对A的所有权，并返回A的地址，然后up置为NULL
    cout << "up1 get() = " << up1.get() << endl;
    auto up2 = up1.release(); // up1释放了而且返回管理的对象给up2, up1失效， up2变成A类型
    cout << "up2 add = " << up2 << endl;
    up2->print();
    delete up2;

    unique_ptr<A> up3(new A(6));
    cout << "up3 get() = " << up3.get() << endl;    
    up3.reset();//释放up3所指的对象A，up3也被释放

    unique_ptr<A> up4(new A(7));
    cout << "up4 get() = " << up4.get() << endl;  
    unique_ptr<A> up5(new A(8));
    cout << "up5 get() = " << up5.get() << endl;  
    //用带参数的reset和release来转移控制权
    up4.reset(up5.release()); //把up5所指的对象转移给up4,并且释放up5
    up4->print();
}
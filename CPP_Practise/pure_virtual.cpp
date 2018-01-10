#include <iostream>
using namespace std;

/* 
******************** 纯虚函数 start*****************************************************************
	慨念：
    所以类纯虚函数的声明就是在告诉子类的设计者，“你必须提供一个纯虚函数的实现，但我不知道你会怎样实现它”。
    当函数没有实现方法或者需要子类来定义实现方法的时候，可以在父类中定义纯虚函数。

    注意：
    不能在类内部为纯虚函数提供定义
    包含纯虚函数的类属于抽象基类，不能直接创建抽象基类的对象

    作用：
	1、为了安全，因为避免任何需要明确但是因为不小心而导致的未知的结果，提醒子类去做应做的实现。
	2、为了效率，不是程序执行的效率，而是为了编码的效率。

	场景： 
	1,当想要在基类中抽象出一个方法，且该类被继承类而不能被实例化时。
	2,基类的方法必须在派生类中被实现时。
	3,多个对象具有公共的抽象属性，但却有不同的实现要求时。
******************** 纯虚函数 end********************************************************************
*/

class animals {
public:
	virtual void move() = 0;
};

class dogs : public animals{
	void move() {cout << "dogs are running" << endl;}
};

class fishes : public animals{
	void move() {cout << "fishes are swiming" << endl;}
};

class birds : public animals{
	void move() {cout << "birds are flying" << endl;}
};


void animalsMoving(animals &a)
{
	a.move();
}

class test{
public:
   virtual void print();
   virtual void order()=0;
   int array[20];
};

//void test::order(){
//   cout << "default order " << endl;
//}

void test::print(){
   order();
   cout << "test:print(): " << endl;
   //for(int i=0; i<20; i++)
           //cout <<  array[i] << endl;
}

class ta : public test {
public:
	void order() {cout << "ta:order" << endl;}
	//void print() {
    	//order();
    	//cout << "ta:print(): " << endl;
    	//for(int i=0; i<20; i++)
           //cout <<  array[i] << endl;
	//}
};

class tb : public ta {
//public:
	void order() {cout << "tb:order" << endl;}
};

class tc : public tb {
	void order() {cout << "tc:order" << endl;}
};


int main() {
	dogs d;
	fishes f;
	birds b;

	animalsMoving(d);
	animalsMoving(f);
	animalsMoving(b);

	ta tao;
	tb tbo;
	tc tco;

	tao.print();
	tbo.print();
	tco.print();
}

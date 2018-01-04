#include <iostream>
using namespace std;

/*
虚函数的作用：实现多态

虚函数的实现： 含有虚函数的类实则是保存一个虚函数列表的地址

虚函数的注意点： 虚函数在子类的参数和类型必须一模一样，否则不是虚函数而是子类函数隐藏基类函数
			   注意向上和向下转型的例子
			    只有类的非静态成员函数才能定义为虚函数，静态成员函数不能定义为虚函数。 
				如果在类外定义虚函数，只能在声明函数时加virtual关键字，定义时不用加。 
				构造函数不能定义为虚函数，虽然可以将operator=定义为虚函数，但最好不要这么做，使用时容易混淆 
				不要在构造函数和析构函数中调用虚函数，在构造函数和析构函数中，对象是不完整的，可能会出现未定义的行为。 
				最好将基类的析构函数声明为虚函数。(析构函数比较特殊，因为派生类的析构函数跟基类的析构函数名称不一样，但是构成覆盖，这里编译器做了特殊处理) 


*********************************************
多态：用父类型的指针指向子类的对象，实现调用实际子类的成员函数
*********************************************

*********************************************
bss: 未初始化和初始化为0的全局变量，只占用运行时的内存空间，而不占用可执行文件自身的文件空间。
data:  已被初始化为非零的全局变量, 既占用运行时的内存空间，也占用可执行文件自身的文件空间。
rodata: 常量数据,字符串会被编译器自动放在rodata中，加 onst关键字的常量数据会被放在rodata中。
text: 代码段
*********************************************
*/

class A {
	int i;//4bytes,对其8bytes
	double j;//8bytes
public:
	A() {i = 1;j=0.1;}
	A(int inti): i(inti) {};
	virtual void virtualFunc() {cout << "A::virtualFunc()" << endl;}// 编译器保存一个虚函数表的地址，存在常量数据rodata中
	virtual void virtualFunc2() {cout << "A::virtualFunc2()" << endl;} // 紧跟在virtualFunc，一个类只会保存一个虚函数表的地址
};

class B: public A {
public:
	B():A(2) {}
	void virtualFunc() {cout << "B::virtualFunc()" << endl;}// B类型有自己虚函数表与A的不一样。
	void virtualFunc2() {cout << "B::virtualFunc2()" << endl;}//函数定义存在代码段中，cout的字符串放在常量数据rodata中。
	//如果B没有对A中virtualFunc2重新定义，将使用A中的virtualFunc2
};

void testFunc(A& a) {
	a.virtualFunc();
}

int main() {
	A ta;
	B tb;

	testFunc(ta);
	testFunc(tb);
}




/*******************************gdb*****************************************

Breakpoint 1, main () at virtual_func_sample.cpp:46
46              A ta;
(gdb) n
47              B tb;
(gdb) 
49              testFunc(ta);
(gdb) p &ta
$1 = (A *) 0x7fffffffc820
(gdb) p sizeof(A)
$2 = 24
(gdb) x/6xw 0x7fffffffc820
0x7fffffffc820: 0x00200330      0x00000000      0x00000001      0x00000000
0x7fffffffc830: 0x9999999a      0x3fb99999
(gdb) x/10xw  0x00200330
0x200330 <_ZTV1A+16>:   0x00201274      0x00000000      0x002012a0      0x00000000
0x200340 <_ZTI1B>:      0x002031b8      0x00000000      0x00200358      0x00000000
0x200350 <_ZTI1B+16>:   0x00200360      0x00000000
(gdb) x/10xw  0x00201274
0x201274 <A::virtualFunc()>:    0xe5894855      0x10ec8348      0xf87d8948      0x2002b1be
0x201284 <A::virtualFunc()+16>: 0x4020bf00      0x11e80020      0xbe000002      0x002014b0
0x201294 <A::virtualFunc()+32>: 0xe8c78948      0x00000224
(gdb) x/50xw 0x0201274
0x201274 <A::virtualFunc()>:    0xe5894855      0x10ec8348      0xf87d8948      0x2002b1be
0x201284 <A::virtualFunc()+16>: 0x4020bf00      0x11e80020      0xbe000002      0x002014b0
0x201294 <A::virtualFunc()+32>: 0xe8c78948      0x00000224      0x00c3c990      0xe5894855
0x2012a4 <A::virtualFunc2()+4>: 0x10ec8348      0xf87d8948      0x2002c2be      0x4020bf00
0x2012b4 <A::virtualFunc2()+20>:        0xe5e80020      0xbe000001      0x002014b0      0xe8c78948
0x2012c4 <A::virtualFunc2()+36>:        0x000001f8      0x00c3c990      0xe5894855      0x10ec8348
0x2012d4 <B::B()+8>:    0xf87d8948      0xf8458b48      0x000002be      0xc7894800
0x2012e4 <B::B()+24>:   0xffff67e8      0x0310baff      0x8b480020      0x8948f845
0x2012f4 <B::B()+40>:   0xc3c99010      0xe5894855      0x10ec8348      0xf87d8948
0x201304 <B::virtualFunc()+12>: 0x2002d4be      0x4020bf00      0x8de80020      0xbe000001
0x201314 <B::virtualFunc()+28>: 0x002014b0      0xe8c78948      0x000001a0      0x00c3c990
0x201324 <B::virtualFunc2()>:   0xe5894855      0x10ec8348      0xf87d8948      0x2002e5be
0x201334 <B::virtualFunc2()+16>:        0x4020bf00      0x61e80020
(gdb) p &tb
$3 = (B *) 0x7fffffffc800
(gdb) x/6xw 0x7fffffffc800
0x7fffffffc800: 0x00200310      0x00000000      0x00000002      0x00000000
0x7fffffffc810: 0xb540fba0      0x00000033
(gdb) x/10xw  0x002000310
0x2000310:      Cannot access memory at address 0x2000310
(gdb) x/10xw  0x00200310
0x200310 <_ZTV1B+16>:   0x002012f8      0x00000000      0x00201324      0x00000000
0x200320 <_ZTV1A>:      0x00000000      0x00000000      0x00200360      0x00000000
0x200330 <_ZTV1A+16>:   0x00201274      0x00000000
(gdb) x/50xw 0x02012f8
0x2012f8 <B::virtualFunc()>:    0xe5894855      0x10ec8348      0xf87d8948      0x2002d4be
0x201308 <B::virtualFunc()+16>: 0x4020bf00      0x8de80020      0xbe000001      0x002014b0
0x201318 <B::virtualFunc()+32>: 0xe8c78948      0x000001a0      0x00c3c990      0xe5894855
0x201328 <B::virtualFunc2()+4>: 0x10ec8348      0xf87d8948      0x2002e5be      0x4020bf00
0x201338 <B::virtualFunc2()+20>:        0x61e80020      0xbe000001      0x002014b0      0xe8c78948
0x201348 <B::virtualFunc2()+36>:        0x00000174      0x00c3c990      0x6666c3f3      0x2e666666
0x201358:       0x00841f0f      0x00000000      0x246c8948      0x64894cd8
0x201368 <__libc_csu_init+8>:   0x8d48e024      0xdfec8f2d      0x258d4cff      0xffdfec88
0x201378 <__libc_csu_init+24>:  0x246c894c      0x74894ce8      0x894cf024      0x48f8247c
0x201388 <__libc_csu_init+40>:  0xd0245c89      0x38ec8348      0x41e5294c      0x8949fd89
0x201398 <__libc_csu_init+56>:  0xfdc148f6      0xd7894903      0x000083e8      0xed854800
0x2013a8 <__libc_csu_init+72>:  0xdb311c74      0x00401f0f      0x4cfa894c      0x8944f689
0x2013b8 <__libc_csu_init+88>:  0x14ff41ef      0xc38348dc
(gdb) x/50iw 0x02012f8
   0x2012f8 <B::virtualFunc()>: push   %rbp
   0x2012f9 <B::virtualFunc()+1>:       mov    %rsp,%rbp
   0x2012fc <B::virtualFunc()+4>:       sub    $0x10,%rsp
   0x201300 <B::virtualFunc()+8>:       mov    %rdi,-0x8(%rbp)
   0x201304 <B::virtualFunc()+12>:      mov    $0x2002d4,%esi
   0x201309 <B::virtualFunc()+17>:      mov    $0x204020,%edi
   0x20130e <B::virtualFunc()+22>:      callq  0x2014a0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
   0x201313 <B::virtualFunc()+27>:      mov    $0x2014b0,%esi
   0x201318 <B::virtualFunc()+32>:      mov    %rax,%rdi
   0x20131b <B::virtualFunc()+35>:      callq  0x2014c0 <_ZNSolsEPFRSoS_E@plt>
   0x201320 <B::virtualFunc()+40>:      nop
   0x201321 <B::virtualFunc()+41>:      leaveq 
   0x201322 <B::virtualFunc()+42>:      retq   
   0x201323:    add    %dl,0x48(%rbp)
   0x201326 <B::virtualFunc2()+2>:      mov    %esp,%ebp
   0x201328 <B::virtualFunc2()+4>:      sub    $0x10,%rsp
   0x20132c <B::virtualFunc2()+8>:      mov    %rdi,-0x8(%rbp)
   0x201330 <B::virtualFunc2()+12>:     mov    $0x2002e5,%esi
   0x201335 <B::virtualFunc2()+17>:     mov    $0x204020,%edi
   0x20133a <B::virtualFunc2()+22>:     callq  0x2014a0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
   0x20133f <B::virtualFunc2()+27>:     mov    $0x2014b0,%esi
   0x201344 <B::virtualFunc2()+32>:     mov    %rax,%rdi
   0x201347 <B::virtualFunc2()+35>:     callq  0x2014c0 <_ZNSolsEPFRSoS_E@plt>
   0x20134c <B::virtualFunc2()+40>:     nop
   0x20134d <B::virtualFunc2()+41>:     leaveq 
   0x20134e <B::virtualFunc2()+42>:     retq   
   0x20134f:    add    %dh,%bl
   0x201351 <__libc_csu_fini+1>:        retq   
   0x201352:    data16 data16 data16 data16 nopw %cs:0x0(%rax,%rax,1)
   0x201360 <__libc_csu_init>:  mov    %rbp,-0x28(%rsp)
   0x201365 <__libc_csu_init+5>:        mov    %r12,-0x20(%rsp)
   0x20136a <__libc_csu_init+10>:       lea    -0x201371(%rip),%rbp        # 0x0
   0x201371 <__libc_csu_init+17>:       lea    -0x201378(%rip),%r12        # 0x0
   0x201378 <__libc_csu_init+24>:       mov    %r13,-0x18(%rsp)
   0x20137d <__libc_csu_init+29>:       mov    %r14,-0x10(%rsp)
   0x201382 <__libc_csu_init+34>:       mov    %r15,-0x8(%rsp)
   0x201387 <__libc_csu_init+39>:       mov    %rbx,-0x30(%rsp)
   0x20138c <__libc_csu_init+44>:       sub    $0x38,%rsp
   0x201390 <__libc_csu_init+48>:       sub    %r12,%rbp
   0x201393 <__libc_csu_init+51>:       mov    %edi,%r13d
   0x201396 <__libc_csu_init+54>:       mov    %rsi,%r14
   0x201399 <__libc_csu_init+57>:       sar    $0x3,%rbp
   0x20139d <__libc_csu_init+61>:       mov    %rdx,%r15
   0x2013a0 <__libc_csu_init+64>:       callq  0x201428 <_init>
   0x2013a5 <__libc_csu_init+69>:       test   %rbp,%rbp
   0x2013a8 <__libc_csu_init+72>:       je     0x2013c6 <__libc_csu_init+102>
   0x2013aa <__libc_csu_init+74>:       xor    %ebx,%ebx
   0x2013ac <__libc_csu_init+76>:       nopl   0x0(%rax)
   0x2013b0 <__libc_csu_init+80>:       mov    %r15,%rdx
   0x2013b3 <__libc_csu_init+83>:       mov    %r14,%rsi

/*******************************gdb*****************************************/
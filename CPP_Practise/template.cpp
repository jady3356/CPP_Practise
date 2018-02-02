#include <iostream>
using namespace std;

template <typename T1, typename T2>
class TA {
public:
	void TF(T1 a,T2 b) {cout << "a = " << a << ", b = " << b << endl;}


};


template<typename a, typename b> 
void temFunc(a& ia, b& ib) {
	cout << "temFunc ia =" << ia << ", ib=" << ib << endl;
}

int main() {
	TA<int, char> ta;
	ta.TF(1,'c');
	int i = 2;
	char c = 'c';
	temFunc(i,c);
	temFunc(c,i);
}
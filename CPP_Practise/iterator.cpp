#include <iostream>
#include <vector>
using namespace std;

/*
(1) 迭代器类型申明和auto的使用
(2) 迭代器的各种操作：*iter:读取实际元素；iter->memeber,读取实际元素的成员；iter1==iter2判断元素是否相等
*/

int main() {
	vector<int> v(10);
	vector<string>::iterator its;//迭代器类型申明
	for(int i=0; i < v.size();i++) {
		v[i] = i;
		cout << v[i] << endl;
	}
	#if 1
    vector<int>::iterator it;//迭代器类型,申明it是一个int型的vector迭代器，让it能够读写vector<int>类型的数据
    for(it = v.begin(); it < v.end(); it++) { // 这里的 < 是什么操作？实际上是一个位置比较，类似于数组index。应该尽量用！=
    	*it = (*it)*(*it);
    }
    #endif
    for(auto itnew = v.begin(); itnew != v.end(); itnew++) { // auto实际上可以推倒出迭代器类型，所以与vector<int>::iterator it;功能一样
    	*itnew = (*itnew)*(*itnew);
    }
    for(auto i:v)
    	cout << i << endl;

}
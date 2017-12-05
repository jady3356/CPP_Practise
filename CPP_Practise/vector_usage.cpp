//#pragma GCC diagnostic error "-std=c++11" 
#include <iostream>
#include <vector>

using namespace std;
/*
(1) 列表初始化，花括号{}和圆括号（）；
(2) 初始化和设定大小只对，个数不多且初始值相同的情况下有必要；
(3) 有用的操作: v.push_back(), v.size(), v.empty()
*/

int main() 
{
	//vector<int> inttest={1,2,3}; //初始化为1,2,3
	//vector<int> inttest{1,2,3}; //初始化为1,2,3
	vector<int> inttest(10);//初始化为10个0
	//vector<int> inttest(10,1);//初始化为10个0
	//vector<int> inttest=(10,1);//错误，没有这个写法
	#if 0
	string word;
	vector<string> vs;
    while(cin >> word){
    	vs.push_back(word);
    	if(getchar() == '\n')
    	break;
    }
    for(auto i : vs)
        cout << i << endl;
    #endif
    for(auto i : inttest)
        cout << i << endl;
    //for(int i = 0; )
}
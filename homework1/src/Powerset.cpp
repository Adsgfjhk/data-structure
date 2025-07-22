#include <iostream>
using namespace std;
void powerset(string s, string a, int n)
{
	if (n == s.length())
		cout << "( " << a << " )" << endl;
	else
	{
		powerset(s, a, n + 1);//先執行遞迴一次，讓空集合可以輸出
		a += s[n];//將使用者自訂的字串加入新的字串中
		powerset(s, a, n + 1);//將新增的字串遞迴會有不同排列方式
	}
}
int main()
{
	string x;
	string a;//使用第二個字串來儲存要輸出的資料
	cin >> x;
	clock_t start = clock();
	powerset(x, a, 0);//n 為記錄該遞迴程式是否到底了
	clock_t stop = clock();
	cout << "花費時間：" << double(stop - start) / CLOCKS_PER_SEC << endl;
}






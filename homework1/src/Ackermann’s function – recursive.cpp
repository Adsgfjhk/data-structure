#include <iostream>
#include <ctime>
using namespace std;
long long Ackermann(long long m, long long n)
{
	if (m == 0)
		return n + 1; //依 Ackermann 函數處理
	else if (m > 0 && n == 0)
		return Ackermann(m - 1, 1); //依 Ackermann 函數處理
	else
		return Ackermann(m - 1, Ackermann(m, n - 1)); //依 Ackermann 函數處理
}
int main()
{
	long long m, n;
	long long a;
	double start, end; //獲取時間用
	double cost;
	start = clock(); //計時開始
	cin >> m >> n;
	a = Ackermann(m, n);
	cout << a << endl;
	end = clock(); //計時結束
	cost = end - start; //計算時間差
	cout << "時間差：" << cost / 1000 << "秒" << endl;
}

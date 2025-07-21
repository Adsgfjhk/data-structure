#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	long long m, n, ans = 0;
	double start, end, cost;
	int x = 2;
	cin >> m >> n;
	start = clock();
	switch (m)//看 m 的不同來對應相對的公式
	{
	case 0:
		n++;
		break;
	case 1:
		n += 2;
		break;
	case 2:
		n = n * 2 + 3;
		break;
	case 3:
		n = pow(2, n + 3) - 3;
		break;
	case 4:
		for (int i = 0; i < n + 2; i++)//m = 4 為 n+3 個 2 的 2 次方
		{
			ans = pow(2, x);
			x = ans;
		}
		n = ans - 3;
		break;
	}
	cout << n << endl;
	end = clock();
	cost = end - start;
	cout << "時間差：" << cost / 1000 << "秒" << endl;
}



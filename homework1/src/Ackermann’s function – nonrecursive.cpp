#include <iostream>
using namespace std;
int main()
{
	long long m, n, ans = 0;
	int x = 2;
	cin >> m >> n;
	clock_t start = clock();
	switch (m)
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
		for (int i = 0; i < n + 2; i++)
		{
			ans = pow(2, x);
			x = ans;
		}
		n = ans - 3;
		break;
	}
	cout << n << endl;
	clock_t stop = clock();
	cout << "花費時間：" << double(stop - start) / CLOCKS_PER_SEC << "秒" << endl;
}



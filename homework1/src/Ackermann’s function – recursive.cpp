#include <iostream>
using namespace std;
long long Ackermann(long long m, long long n)
{
	if (m == 0)
		return n + 1;
	else if (m > 0 && n == 0)
		return Ackermann(m - 1, 1);
	else
		return Ackermann(m - 1, Ackermann(m, n - 1));
}
int main()
{
	long long m, n;
	long long a;
	clock_t start = clock();
	cin >> m >> n;
	a = Ackermann(m, n);
	cout << a << endl;
	clock_t stop = clock();
	cout << "花費時間：" << double(stop - start) / CLOCKS_PER_SEC << "秒" << endl;
}

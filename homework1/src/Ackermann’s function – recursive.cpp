#include <iostream>
#include <ctime>
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
	double start, end; 
	double cost;
	start = clock(); 
	cin >> m >> n;
	a = Ackermann(m, n);
	cout << a << endl;
	end = clock(); 
	cost = end - start; 
	cout << "時間差：" << cost / 1000 << "秒" << endl;
}

#include <iostream>
using namespace std;
void powerset(string s, string a, int n)
{
	if (n == s.length())
		cout << "( " << a << " )" << endl;
	else
	{
		powerset(s, a, n + 1);
		a += s[n];
		powerset(s, a, n + 1);
	}
}
int main()
{
	string x;
	string a;
	double start, end, cost;
	cin >> x;
	start = clock();
	powerset(x, a, 0);
	end = clock();
	cost = end - start;
	cout << "時間差：" << cost / 1000 << endl;
}



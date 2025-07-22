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
	cin >> x;
	clock_t start = clock();
	powerset(x, a, 0);
	clock_t stop = clock();
	cout << "花費時間：" << double(stop - start) / CLOCKS_PER_SEC << endl;
}






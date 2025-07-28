#include <iostream>
#include <cstdio>
using namespace std;
class Polynomial; //forward declaration
class Term {
	friend Polynomial;
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator<<(istream& in, Polynomial& p);
private:
	float coef; //係數
	int exp; //指數
};
class Polynomial {
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& input, Polynomial& p);
private:
	Term* termArray; //多項式中非零項的陣列
	int capacity; //termArrayの大小
	int terms; //非零項的數目
public:
	Polynomial(); // Construct the polynomial p(x) = 0.
	Polynomial Add(Polynomial poly); // Return the sum of the polynomial*thisand poly.
	Polynomial Mult(Polynomial poly); // Return the product of thepolynomials* thisand poly.
	void NewTerm(const int newCoef, const int newExp); //新增項目
	float Eval(float f); //Evaluate the polynomial *this at f and returnthe result;
	
};
Polynomial::Polynomial() :capacity(2), terms(0) {
	termArray = new Term[capacity];
}
void Polynomial::NewTerm(const int newCoef, const int newExp) {
	if (terms == capacity) { //空間不足時重新配置空間
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, this->termArray + terms, temp);
		delete[] termArray;
		termArray = temp;
	}
	termArray[terms].coef = newCoef;
	termArray[terms++].exp = newExp;
}
float Polynomial::Eval(float f) 
{ //多項式求值
	int total = 0;
	for (int i = 0; i < terms; i++) { //走訪terms
		total += termArray[i].coef * pow(f, termArray[i].exp);
	}
	return total; //回傳最終計算值
}
Polynomial Polynomial::Add(Polynomial poly) {
	Polynomial ans;
	int a = 0, b = 0;

	while ((a < terms) && (b < poly.terms))
	{
		if (termArray[a].exp == poly.termArray[b].exp)
		{
			float x = termArray[a].coef + poly.termArray[b].coef;
			if (x)
				ans.NewTerm(x, termArray[a].exp);
			a++;
			b++;
		}
		else if (termArray[a].exp < poly.termArray[b].exp)
		{
			ans.NewTerm(poly.termArray[b].coef, poly.termArray[b].exp);
			b++;
		}
		else
		{
			ans.NewTerm(termArray[a].coef, termArray[a].exp);
			a++;
		}
	}
	for (; a < terms; a++)
	{
		ans.NewTerm(termArray[a].coef, termArray[a].exp);
	}
	for (; b < terms; b++)
	{
		ans.NewTerm(poly.termArray[b].coef, poly.termArray[b].exp);
	}
	return ans;
}
ostream& operator<<(ostream& os, const Polynomial& p) {
	for (int i = 0; i < p.terms; i++) {
		if (p.termArray[i].exp == 0) { //判斷若為常數，只輸出數字
			os << p.termArray[i].coef;
			continue;
		}
		if (i == p.terms - 1) //ax^n
		{
			os << p.termArray[i].coef << "X^" << p.termArray[i].exp;
		}
		else //+ax^n
		{
			os << p.termArray[i].coef << "X^" << p.termArray[i].exp<< "+";
		}
	}
	return os;
}
istream& operator>>(istream& in, Polynomial& p)
{
	int x, y;
	char c;
	while (1) {
		in >> x;//係數
		c = getchar();//拿掉X的字元
		c = getchar();//拿掉Y的字元
		in >> y;//次方
		c = getchar();//拿掉+
		p.NewTerm(x, y);//將輸入的值傳進去多項式中
		if (c == '\n') break;
	}
	return in;
}
Polynomial Polynomial::Mult(Polynomial poly) {
	Polynomial ans, num;
	int* ch;
	int check;
	for (int i = 0; i < terms; i++) //走訪自己的Term陣列
	{ 
		for (int j = 0; j < poly.terms; j++) //走訪參數poly的Term陣列
		{ 
			ans.NewTerm(termArray[i].coef * poly.termArray[j].coef, poly.termArray[i].exp + poly.termArray[j].exp);	
		}
	}
	ch = new int[ans.terms];
	for (int d = 0; d < ans.terms; d++)
		ch[d] = 0;
	for (int i = 0; i < ans.terms; i++)
	{
		float total = 0;
		int f = 1;
		check = 1;
		if (ans.termArray[i].exp == 0)
		{
			num.NewTerm(ans.termArray[i].coef, ans.termArray[i].exp);
			break;
		}
		for (int j = i + 1; j < ans.terms; j++)
		{
			if (ans.termArray[i].exp == ans.termArray[j].exp && f)
			{
				total += ans.termArray[i].coef + ans.termArray[j].coef;
				f = 0;
			}
			else if (ans.termArray[i].exp == ans.termArray[j].exp)
			{
				total += ans.termArray[j].coef;
			}
		}
		for (int c = 0; c < ans.terms; c++)
		{
			if ((ans.termArray[i].exp) != (ch[c]))
			{
				check = 1;
			}
			else
			{
				check = 0;
				break;
			}
		}
		if (total)
		{
			if (check)
				num.NewTerm(total, ans.termArray[i].exp);
		}
		else
		{
			if (check)
				num.NewTerm(ans.termArray[i].coef, ans.termArray[i].exp);
		}
		ch[i] = ans.termArray[i].exp;
	}
	delete[] ch;
	return num;
}

int main() {
	Polynomial p1, p2;
	int x;
	cout << "請輸入第一個多項式";
	cin >> p1;
	cout << "請輸入第二個多項式";
	cin >> p2;
	cout << "請輸入X的值";
	cin >> x;
        clock_t start = clock(); //計時開始
	cout << "p1.Eval(x)    = " << p1.Eval(x) << endl;
	cout << "p2.Eval(x)    = " << p2.Eval(x) << endl;
	cout << "p1.Add(p2)    = " << p1.Add(p2) << endl;
	cout << "p1.Mult(p2)   = " << p1.Mult(p2) << endl;
	clock_t stop = clock(); //計時結束
	cout << "花費時間：" << double(stop - start) / CLOCKS_PER_SEC << "秒" << endl;
	return 0;
}

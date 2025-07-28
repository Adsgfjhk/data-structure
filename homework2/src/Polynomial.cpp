#include <iostream>
#include <cstdio>
using namespace std;
class Polynomial; 

class Term {
	friend Polynomial;
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator<<(istream& in, Polynomial& p);
private:
	float coef; 
	int exp; 
};

class Polynomial {
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& input, Polynomial& p);
private:
	Term* termArray; 
	int capacity;  
	int terms; 
public:
	Polynomial();    
	Polynomial Add(Polynomial poly);   
	Polynomial Mult(Polynomial poly); 
	void NewTerm(const int newCoef, const int newExp); 
	float Eval(float f);  

};

Polynomial::Polynomial() :capacity(2), terms(0) {
	termArray = new Term[capacity];
}

void Polynomial::NewTerm(const int newCoef, const int newExp) {
	if (terms == capacity) { 
		capacity *= 2;
		Term* temp = new Term[capacity];
		copy(termArray, this->termArray + terms, temp);
		delete[] termArray;
		termArray = temp;
	}
	termArray[terms].coef = newCoef;
	termArray[terms++].exp = newExp;
}
float Polynomial::Eval(float value)
{ 
	int total = 0;
	for (int i = 0; i < terms; i++) {    
		total += termArray[i].coef * pow(value, termArray[i].exp);
	}
	return total; 
}

Polynomial Polynomial::Add(Polynomial poly) {
	Polynomial result;
	int thisIndex = 0, otherIndex = 0;
	
	while ((thisIndex < terms) && (otherIndex < poly.terms))
	{
		if (termArray[thisIndex].exp == poly.termArray[otherIndex].exp)
		{
			
			float x = termArray[thisIndex].coef + poly.termArray[otherIndex].coef;
			if (x)
				result.NewTerm(x, termArray[thisIndex].exp);
			thisIndex++;
			otherIndex++;
		}
		else if (termArray[thisIndex].exp < poly.termArray[otherIndex].exp)
		{
			
			result.NewTerm(poly.termArray[otherIndex].coef, poly.termArray[otherIndex].exp);
			otherIndex++;
		}
		else
		{
			
			result.NewTerm(termArray[thisIndex].coef, termArray[thisIndex].exp);
			thisIndex++;
		}
	}
	
	for (; thisIndex < terms; thisIndex++)
	{
		result.NewTerm(termArray[thisIndex].coef, termArray[thisIndex].exp);
	}

	for (; otherIndex < terms; otherIndex++)
	{
		result.NewTerm(poly.termArray[otherIndex].coef, poly.termArray[otherIndex].exp);
	}
	return result;
}

ostream& operator<<(ostream& os, const Polynomial& p) {
	for (int i = 0; i < p.terms; i++) {
		if (p.termArray[i].exp == 0) {
			os << p.termArray[i].coef;
			continue;
		}
		if (i == p.terms - 1) 	    
		{
		
			os << p.termArray[i].coef << "X^" << p.termArray[i].exp;
		}
		else 
		{
		
			os << p.termArray[i].coef << "X^" << p.termArray[i].exp << "+";
		}
	}
	return os;
}
istream& operator>>(istream& in, Polynomial& p)
{
	int x, y;
	char c;
	while (1) {
		in >> x;
		c = getchar();
		c = getchar();
		in >> y;
		c = getchar();
		p.NewTerm(x, y);
		if (c == '\n') break;		 
	}
	return in;
}
Polynomial Polynomial::Mult(Polynomial poly) {
	Polynomial ans, num;  
	int* ch;	
	int check;
	for (int i = 0; i < terms; i++)    
	{
		for (int j = 0; j < poly.terms; j++) 
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
	clock_t start = clock();
	cout << "p1.Eval(x)    = " << p1.Eval(x) << endl;
	cout << "p2.Eval(x)    = " << p2.Eval(x) << endl;	
	cout << "p1.Add(p2)    = " << p1.Add(p2) << endl;		
	cout << "p1.Mult(p2)   = " << p1.Mult(p2) << endl;	
	clock_t stop = clock(); 
	cout << "花費時間：" << double(stop - start) / CLOCKS_PER_SEC << "秒" << endl;
	return 0;
}

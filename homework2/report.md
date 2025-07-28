# 41143231

作業二

### Polynomial
## 解題說明

加法功能(Add):
先宣告一個 `result` 來儲存兩多項式相加的結果，再宣告`thisIndex`、`otherIndex`來表示要相加的兩個多項式的項數。透過兩個指標移動，如果兩個指標指到的項次方數相同，則將係數相加，加到結果多項式中;如果`thisIndex`的該項指標次方數<`otherIndex`的該項指標次方數，則將`otherIndex`該項直接加入到結果多項式中; 如果`thisIndex`的該項指標次方數>`otherIndex`的該項指標次方數，則將`thisIndex`該項直接加入到結果多項式中。

乘法功能(Mult):
	 先宣告`ans`與`num`兩個，`ans`負責儲存相乘完後的結果，`num` 為`ans` 乘完相加後的結果。使用兩個`for`迴圈來將`ans`相同次方的數相加，兩個`for` 迴圈的判斷式都是要跑到`ans` 的非零項最後，宣告`total`來儲存次方相同相加過後的數，並使用陣列 `ch` 記錄已處理的指數，避免重複。
 
求值(Eval):
	利用使用者輸入的`value`來當作多項式X的值，將其代入多項式的每項中，計算每項的數值，並將其全部加起來。
 
輸入:
	標準輸入格式為 "係數X^指數+..."（如 $"3X^2+1X^0"$），循環讀取係數 (x) 和指數 (y)，使用 getchar() 移除 'X'、'^' 和 '+'，將每項通過 `NewTerm` 加入多項式，當遇到換行符 (\n) 時停止。
 
輸出:
	依序將多項式，輸出多項式的係數，並加上”X^指數”，如果指數次方為0，則只輸出係數，並判斷是否為最後項，如果是，則不輸出”+”，反之，則在每項後輸出”+”。



## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
class Polynomial; 
// Term 類表示多項式中的單個項（係數和指數）
class Term {
	friend Polynomial;
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator<<(istream& in, Polynomial& p);
private:
	float coef; //係數
	int exp; //指數
};
// Polynomial 類表示一個由項陣列組成的多項式
class Polynomial {
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& input, Polynomial& p);
private:
	Term* termArray; // 儲存非零項的陣列
	int capacity;  // termArray 的大小
	int terms; // 非零項的數量
public:
	Polynomial();    // 建構函數：初始化一個空的多項式
	Polynomial Add(Polynomial poly);   // 回傳此多項式與另一多項式的和
	Polynomial Mult(Polynomial poly); //此多項式與另一多項式的乘積
	void NewTerm(const int newCoef, const int newExp); //新增項目
	float Eval(float f);  // 計算多項式在指定值時的結果

};
// 建構函數：初始化多項式
Polynomial::Polynomial() :capacity(2), terms(0) {
	termArray = new Term[capacity];
}
// 新增一個新項，包含係數和指數
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
float Polynomial::Eval(float value)
{ //多項式求值
	int total = 0;
	for (int i = 0; i < terms; i++) {     // 對每個項計算：係數 * value^指數
		total += termArray[i].coef * pow(value, termArray[i].exp);
	}
	return total; //回傳最終計算值
}
// 將此多項式與另一多項式相加，回傳結果
Polynomial Polynomial::Add(Polynomial poly) {
	Polynomial result;
	int thisIndex = 0, otherIndex = 0;
	// 根據指數合併兩個多項式的項
	while ((thisIndex < terms) && (otherIndex < poly.terms))
	{
		if (termArray[thisIndex].exp == poly.termArray[otherIndex].exp)
		{
			// 相同指數：係數相加
			float x = termArray[thisIndex].coef + poly.termArray[otherIndex].coef;
			if (x)
				result.NewTerm(x, termArray[thisIndex].exp);
			thisIndex++;
			otherIndex++;
		}
		else if (termArray[thisIndex].exp < poly.termArray[otherIndex].exp)
		{
			// 複製另一多項式的項
			result.NewTerm(poly.termArray[otherIndex].coef, poly.termArray[otherIndex].exp);
			otherIndex++;
		}
		else
		{
			// 複製此多項式的項
			result.NewTerm(termArray[thisIndex].coef, termArray[thisIndex].exp);
			thisIndex++;
		}
	}
	// 複製此多項式剩餘的項
	for (; thisIndex < terms; thisIndex++)
	{
		result.NewTerm(termArray[thisIndex].coef, termArray[thisIndex].exp);
	}
	// 複製另一多項式剩餘的項
	for (; otherIndex < terms; otherIndex++)
	{
		result.NewTerm(poly.termArray[otherIndex].coef, poly.termArray[otherIndex].exp);
	}
	return result;
}
// 將多項式輸出到流，以可讀格式顯示
ostream& operator<<(ostream& os, const Polynomial& p) {
	for (int i = 0; i < p.terms; i++) {
		if (p.termArray[i].exp == 0) { //判斷若為常數，只輸出數字
			os << p.termArray[i].coef;
			continue;
		}
		if (i == p.terms - 1) 	    
		{
			// 最後一項：不加加號
			os << p.termArray[i].coef << "X^" << p.termArray[i].exp;
		}
		else 
		{
			// 非最後一項：包含加號
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
		in >> x;//係數
		c = getchar();//拿掉X的字元
		c = getchar();//拿掉Y的字元
		in >> y;//次方
		c = getchar();//拿掉+
		p.NewTerm(x, y);//將輸入的值傳進去多項式中
		if (c == '\n') break;		  // 遇到換行符結束
	}
	return in;
}
Polynomial Polynomial::Mult(Polynomial poly) {
	Polynomial ans, num;   // ans 儲存中間結果，num 儲存最終結果
	int* ch;	// 用於記錄已處理的指數
	int check;
	for (int i = 0; i < terms; i++)      // 生成所有可能的項乘積
	{
		for (int j = 0; j < poly.terms; j++) 
		{
			ans.NewTerm(termArray[i].coef * poly.termArray[j].coef, poly.termArray[i].exp + poly.termArray[j].exp);
		}
	}
	ch = new int[ans.terms];
	for (int d = 0; d < ans.terms; d++)
		ch[d] = 0;
	// 合併相同指數的項
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
		for (int j = i + 1; j < ans.terms; j++)	       // 對相同指數的項求和係數
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
		for (int c = 0; c < ans.terms; c++)	    // 檢查指數是否已處理
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
		if (total)	       // 若係數非零且指數唯一，加入結果
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
	cout << "p1.Eval(x)    = " << p1.Eval(x) << endl;// 計算 p1 在 x 的值
	cout << "p2.Eval(x)    = " << p2.Eval(x) << endl;	  // 計算 p2 在 x 的值
	cout << "p1.Add(p2)    = " << p1.Add(p2) << endl;		// 輸出 p1 + p2
	cout << "p1.Mult(p2)   = " << p1.Mult(p2) << endl;	 // 輸出 p1 * p2
	clock_t stop = clock(); //計時結束
	cout << "花費時間：" << double(stop - start) / CLOCKS_PER_SEC << "秒" << endl;
	return 0;
}
```

## 效能分析

|      | 時間複雜度 | 空間複雜度 |
|----------|--------------|----------|
| Add   | $O（m + n）$      | $m + n$         |
| Mult   | $O（x * y + z^2）$      | $z$          |
| Eval   | $O（n）$      |  $1$         |
| ostream   | $O（n）$      |  $1$        |
| istream   | $O（n）$     |  $1$  |

## 測試與驗證

### 測試案例

1

    p1: (2X^2+2X^1+2X^0)
  
    P2: (2X^2+2X^1+2X^0)
  
    代入數字:2

![show](https://github.com/Adsgfjhk/data-structure/blob/main/homework2/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-28%20235004.png)



### 結論

這個作業使用了動態陣列儲存多項式的項（係數與指數），支援兩個多項式相加，合併同類項，實現多項式乘法，計算所有項的乘積並合併同類項，計算多項式在給定 x 值時的結果，支援格式化的多項式輸入與輸出。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用動態陣列來儲存多項式的項原因如下：

1. **靈活的儲存空間**  
   多項式的項數（非零項）在執行時可能會變化，且事先無法確定項的數量。動態陣列允許在需要時動態分配或重新分配記憶體（如程式碼中的 `capacity *= 2`），避免固定大小陣列可能導致的空間不足或浪費。

用遞迴將這一定義寫成程式碼，易於理解和實現。

2. **高效的記憶體管理**  
   動態陣列只分配實際需要的空間，初始容量較小（如程式碼中的 `capacity = 2`），並在需要時成倍擴展（`capacity *= 2`）。這在項數未知的情況下能有效減少記憶體浪費，同時確保足夠的儲存空間。

3. **支援動態新增項**  
   程式碼中的 `NewTerm` 方法允許在執行時動態添加新項，並在空間不足時重新分配陣列（realloc 的效果）。這對於使用者輸入多項式（如 `cin >> p1`）或計算結果（如 Add 和 Mult）時非常重要。

4. **避免靜態陣列的限制**  
   若使用靜態陣列，必須預先定義固定大小，可能導致陣列過小，無法儲存所有項:陣列過大，浪費記憶體。 動態陣列通過 `new` 和 `delete`（如程式碼中的 `delete[]` `termArray`）解決這些問題。
   
使用動態陣列儲存多項式的項能夠提供靈活的記憶體管理、適應動態項數變化，並支援高效的多項式操作（如加法、乘法和求值）。這在處理大小不確定或運行時變化的多項式時尤為重要，同時避免了靜態陣列的限制和浪費。

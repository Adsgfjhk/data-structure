# 41143231

作業一

### Ackermann’s function – recursive
## 解題說明

利用題目給的公式，用 `if` 來判斷當時的情況並作相對應的處理。


## 程式實作

以下為主要程式碼：

```cpp
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
	clock_start = clock(); //計時開始
	cin >> m >> n;
	a = Ackermann(m, n);
	cout << a << endl;
	clock_t = clock(); //計時結束
	cout << "花費時間：" << double(stop - start)/CLOCKS_PER_SEC << "秒" << endl;
}

```

## 效能分析

1. 時間複雜度：Ackermann函數的遞迴成長過快，超過了 $Big O$ 的範圍，算不出來。
2. 空間複雜度：Ackermann函數的遞迴成長過快，超過了 $Big O$ 的範圍，算不出來。

## 測試與驗證

### 測試案例

1、m = 0, n <= 9223372036854775806

![1](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20013201.png)

2、m = 1,n <= 4539

![2](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20020233.png)

3、m = 2,n <= 2265

![3](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20020302.png)

4、m = 3, n <= 9

![4](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20020321.png)

5、 m = 4, n <= 0

![5](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20020333.png)


### 結論

輸入兩個正整數`m`和`n`，通過遞迴實現Ackermann函數。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算Ackermann函數的主要原因如下：

1. **符合函數定義**  
   Ackermann 函數的數學定義本身就是遞迴的，包含三個條件：
- $A(m, n) = n + 1 （當  m = 0）$
- $A(m, n) = A(m-1, 1)（當 m > 0, n = 0）$
- $A(m, n) = A(m-1, A(m, n-1))（當 m > 0, n > 0）$

用遞迴將這一定義寫成程式碼，易於理解和實現。

2. **易於理解與實現**  
   Ackermann 函數的計算過程非常複雜，特別是對於較大的m和n，其增長值極大，若使用迭代實現起來更為複雜，且可讀性較低，而遞迴做起來更直觀也簡化了程式碼。

當  $m \geq 4$  且  $n$  為中間值時，這個函數可能因為遞迴太多而超過堆疊限制，或是導致明顯的執行延遲。程式使用 `clock()` 函數來測量 CPU 時間，單位為毫秒，並會轉換成秒以方便閱讀。測試顯示，若輸入 $m = 3, n = 3$ 通常幾毫秒就能跑完；但若輸入 $m = 4, n = 1$ 可能需要花幾秒鐘，輸入加大時還有堆疊溢出的風險。

### Ackermann’s function – nonrecursive
## 解題說明

利用維基百科阿克曼函數表中的 `n` 公式，用 `switch` 來判斷 `m` 的數值，並做
出對應的解題方法。

![公式](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E5%85%AC%E5%BC%8F.png)


## 程式實作

以下為主要程式碼：

```cpp
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



```

## 效能分析

1. 時間複雜度：
 ```cpp
if (n < 4)
	9 + 2 = 11
if (n > = 4)
	9 + (n + 3) + 2 * (n + 2) + 2 = 3n + 16
   ```
2. 空間複雜度：8 //m、n、ans、start、end、cost、x、i

## 測試與驗證

### 測試案例

1、m = 0, n <= 9223372036854775806

![6](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20110945.png)

2、m = 1, n <= 9223372036854775805

![7](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20111411.png)

3、m = 2, n <= 4611686018427387902

![8](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20111537.png)

4、m = 3, n <= 59

![9](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20111618.png)

5、m = 4, n <= 2

![10](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20111714.png)

### 結論

程式透過輸入兩個整數 $m$ 和 $n$，根據 $m$ 的值（範圍從 0 到 4）對 $n$ 執行不同的數學運算：
- 當 $m = 0$ 時，計算 $n + 1$。
- 當 $m = 1$ 時，計算 $n + 2$。
- 當 $m = 2$ 時，計算 $2n + 3$。
- 當 $m = 3$ 時，計算 $2^{n+3} - 3$。
- 當 $m = 4$ 時，迭代計算 2 的冪次（共 $n+2$ 次）後減 3。
最後，程式輸出計算後的 $n$ 值。

## 申論及開發報告

### 選擇迭代的原因

在本程式中，使用迭代的主要原因如下：

1. **實現多重冪次運算：**  
   當 `m = 4` 時，程式需要計算一個多重冪次，例如對於 `n = 2`，等價於 `2^(2^(2^...))`（共 `n + 2` 次冪運算）。這種運算無法通過單次 `pow` 函數直接實現，因為內層冪次的值需要前一次計算的結果。因此，使用迴圈迭代是自然且直接的方式，每次計算 `pow(2, x)` 並將結果作為下一次的指數。

2. **模擬遞迴性質**  
  多重冪次運算本質上是一個遞迴過程（例如，`2^(2^x)`），但在 C++ 中，遞迴函數可能因遞迴層次過高而導致堆疊溢位。使用迭代（`for` 迴圈）可以避免遞迴的性能消耗，特別是當 `n` 較大時，迭代更安全且記憶體效率更高。

3. **直觀性**  
   對於 $n + 2$次的冪次計算，使用 for 迴圈是一種簡單且直觀的實現方式。相比之下，嘗試將多重冪次寫成單一數學公式或複雜的遞迴函數可能更難以維護和理解。

透過輸入處理，使用 `switch`、`pow`、迭代迴圈和 `clock` 等方法，實現對 `n` 的不同數學轉換並記錄執行時間。
### Powerset
## 解題說明

利用第二個陣列來儲存要輸出的值，之後將排列完的再次執行遞迴，並且到底後輸出該字串

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
using namespace std;
void powerset(string s, string a, int n)
{
	if (n == s.length())
		cout << "( " << a << " )" << endl;
	else
	{
		powerset(s, a, n + 1);//先執行遞迴一次，讓空集合可以輸出
		a += s[n];//將使用者自訂的字串加入新的字串中
		powerset(s, a, n + 1);//將新增的字串遞迴會有不同排列方式
	}
}
int main()
{
	string x;
	string a;//使用第二個字串來儲存要輸出的資料
	double start, end, cost;
	cin >> x;
	start = clock();
	powerset(x, a, 0);//n 為記錄該遞迴程式是否到底了
	end = clock();
	cost = end - start;
	cout << "時間差：" << cost / 1000 << endl;
}



```

## 效能分析

1. 時間複雜度： $O(2^n)$ //n 為 s 字串長度
2. 空間複雜度： $O(n)$ //n 為 s 字串長度

## 測試與驗證

### 測試案例

1、有18 個數字，總共要跑13.372 秒。

![11](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20112038.png)

2、有20 個數字，總共要跑52.217 秒。

![12](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20112116.png)



### 結論

輸入字串 `x` ， `powerset` 函數採用遞迴方式，輸出輸入字串的所有子集合，包括空集合，並以括號格式顯示。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式碼簡潔性與可讀性**  
  遞迴方法只需少量程式碼即可完成幂集生成。程式碼如下:
 ```cpp
   if (n == s.length())
    cout << "( " << a << " )" << endl;
else
{
    powerset(s, a, n + 1); // 不包含當前字元
    a += s[n]; // 包含當前字元
    powerset(s, a, n + 1); // 遞迴處理下一個字元
}
   ```

2. **符合定義**  
   遞迴能將大問題（生成整個幂集）分解為小問題（處理剩餘字元的幂集），並利用函數自動保存當前狀態（字串 a 和索引 n）。
   在程式碼中，`powerset(string s, string a, int n)` 函數通過兩次遞迴實現：
- `powerset(s, a, n + 1)`：不包含當前字元 s[n]，保持 a 不變。
- `powerset(s, a + s[n], n + 1)`：包含當前字元，將 s[n] 追加到 a。
當 n 達到字串長度`（n == s.length()）`，輸出當前子集 a。

這種遞迴設計直接映射到幂集的生成過程，每個字元的選擇生成一個分支，最終列舉所有 2^n 個子集。



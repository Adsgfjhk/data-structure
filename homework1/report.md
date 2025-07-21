# 41143231

作業一

### Ackermann’s function – recursive
## 解題說明

利用題目給的公式，用 if 來判斷當時的情況並作相對應的處理。


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
	start = clock(); //計時開始
	cin >> m >> n;
	a = Ackermann(m, n);
	cout << a << endl;
	end = clock(); //計時結束
	cost = end - start; //計算時間差
	cout << "時間差：" << cost / 1000 << "秒" << endl;
}

```

## 效能分析

1. 時間複雜度：阿克曼函數的遞迴成長過快，超過了 Big O 的範圍，算不出來。
2. 空間複雜度：阿克曼函數的遞迴成長過快，超過了 Big O 的範圍，算不出來。

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

輸入兩個正整數m和n，通過遞迴實現Ackermann函數。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算Ackermann函數的主要原因如下：

1. **符合函數定義**  
   Ackermann 函數的數學定義本身就是遞迴的，包含三個條件：

- A(m, n) = n + 1 （當  m = 0）
- A(m, n) = A(m-1, 1)（當 m > 0, n = 0）
- A(m, n) = A(m-1, A(m, n-1))（當 m > 0, n > 0）

遞迴直接將這一定義轉化為程式碼，易於理解和實現。

2. **易於理解與實現**  
   Ackermann 函數的計算過程非常複雜，特別是對於較大的m和n，其增長值極大。若使用迭代需要手動管理，實現起來更為複雜，且可讀性較低。而遞迴方法則讓系統自動管理函數調用，簡化了程式碼。

當  $m \geq 4$  且  n  為中間值時，這個函數可能因為遞迴太多而超過堆疊限制，或是導致明顯的執行延遲。程式使用 `clock()` 函數來測量 CPU 時間，單位為毫秒，並會轉換成秒以方便閱讀。測試顯示，若輸入  m = 3, n = 3 通常幾毫秒就能跑完；但若輸入  m = 4, n = 1 可能需要花幾秒鐘，輸入加大時還有堆疊溢出的風險。

### Ackermann’s function – nonrecursive
## 解題說明

利用維基百科阿克曼函數表中的 n 公式，用 switch 來判斷 m 的數值，並做
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
- 當 $m = 0$ 時，n + 1。
- 當 $m = 1$ 時，n + 2。
- 當 $m = 2$ 時，2n + 3。
- 當 $m = 3$ 時，計算 $2^{n+3} - 3$。
- 當 $m = 4$ 時，迭代計算 2 的冪次（共 $n+2$ 次）後減 3。
最後，程式輸出計算後的 $n$ 值。
$n + 1$
## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。
### Powerset
## 解題說明

利用第二個陣列來儲存要輸出的值，之後將排列完的再次執行遞迴，並且
到底後輸出該字串


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

1. 時間複雜度：O(2^n) //n 為 s 字串長度
2. 空間複雜度：O(n) //n 為 s 字串長度

## 測試與驗證

### 測試案例

1、有18 個數字，總共要跑13.372 秒。

![11](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20112038.png)

2、有20 個數字，總共要跑52.217 秒。

![12](https://github.com/Adsgfjhk/data-structure/blob/main/homework1/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-07-21%20112116.png)



### 結論

1. 程式能正確計算 $n$ 到 $1$ 的連加總和。  
2. 在 $n < 0$ 的情況下，程式會成功拋出異常，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$n = 1$、$n > 1$、$n < 0$），驗證程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **程式邏輯簡單直觀**  
   遞迴的寫法能夠清楚表達「將問題拆解為更小的子問題」的核心概念。  
   例如，計算 $\Sigma(n)$ 的過程可分解為：  

   $$
   \Sigma(n) = n + \Sigma(n-1)
   $$

   當 $n$ 等於 1 或 0 時，直接返回結果，結束遞迴。

2. **易於理解與實現**  
   遞迴的程式碼更接近數學公式的表示方式，特別適合新手學習遞迴的基本概念。  
   以本程式為例：  

   ```cpp
   int sigma(int n) {
       if (n < 0)
           throw "n < 0";
       else if (n <= 1)
           return n;
       return n + sigma(n - 1);
   }
   ```

3. **遞迴的語意清楚**  
   在程式中，每次遞迴呼叫都代表一個「子問題的解」，而最終遞迴的返回結果會逐層相加，完成整體問題的求解。  
   這種設計簡化了邏輯，不需要額外變數來維護中間狀態。

透過遞迴實作 Sigma 計算，程式邏輯簡單且易於理解，特別適合展示遞迴的核心思想。然而，遞迴會因堆疊深度受到限制，當 $n$ 值過大時，應考慮使用迭代版本來避免 Stack Overflow 問題。

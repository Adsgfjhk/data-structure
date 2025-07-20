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

1. 時間複雜度：阿克曼函數的遞迴成長過快，超過了 Big o 的範圍，算不出來。
2. 空間複雜度：阿克曼函數的遞迴成長過快，超過了 Big o 的範圍，算不出來。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $n = 0$      | 0        | 0        |
| 測試二   | $n = 1$      | 1        | 1        |
| 測試三   | $n = 3$      | 6        | 6        |
| 測試四   | $n = 5$      | 15       | 15       |
| 測試五   | $n = -1$     | 異常拋出 | 異常拋出 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

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

### Ackermann’s function – nonrecursive
## 解題說明

利用維基百科阿克曼函數表中的 n 公式，用 switch 來判斷 m 的數值，並做
出對應的解題方法。


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

| 測試案例 | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   | $n = 0$      | 0        | 0        |
| 測試二   | $n = 1$      | 1        | 1        |
| 測試三   | $n = 3$      | 6        | 6        |
| 測試四   | $n = 5$      | 15       | 15       |
| 測試五   | $n = -1$     | 異常拋出 | 異常拋出 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sigma sigma.cpp
$ ./sigma
6
```

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

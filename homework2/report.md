# 41143231

作業二

### Ackermann’s function – recursive
## 解題說明

加法功能(Add):
先宣告一個 result 來儲存兩多項式相加的結果，，再宣告thisIndex、otherIndex來表示要相加的兩個多項式的項數。透過兩個指標移動，如果兩個指標指到的項次方數相同，則將係數相加，加到結果多項式中;如果thisIndex的該項指標次方數<otherIndex的該項指標次方數，則將b該項直接加入到結果多項式中; 如果thisIndex的該項指標次方數>otherIndex的該項指標次方數，則將thisIndex該項直接加入到結果多項式中。

乘法功能(Mult):
	 先宣告ans與num兩個，ans負責儲存相乘完後的結果，num 為ans 乘完相加後的結果。使用兩個for迴圈來將ans相同次方的數相加，兩個for 迴圈的判斷式都是要跑到ans 的非零項最後，宣告total來儲存次方相同相加過後的數，並使用陣列 ch 記錄已處理的指數，避免重複。
 
求值(Eval):
	利用使用者輸入的value來當作多項式X的值，將其代入多項式的每項中，計算每項的數值，並將其全部加起來。
 
輸入:
	標準輸入格式為 "係數X^指數+..."（如 "3X^2+1X^0"），循環讀取係數 (x) 和指數 (y)，使用 getchar() 移除 'X'、'^' 和 '+'，將每項通過 NewTerm 加入多項式，當遇到換行符 (\n) 時停止。
 
輸出:
	依序將多項式，輸出多項式的係數，並加上”X^指數”，如果指數次方為0，則只輸出係數，並判斷是否為最後項，如果是，則不輸出”+”，反之，則在每項後輸出”+”。



## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
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
	clock_t start = clock(); //計時開始
	cin >> m >> n;
	a = Ackermann(m, n);
	cout << a << endl;
	clock_t stop = clock(); //計時結束
	cout << "花費時間：" << double(stop - start) / CLOCKS_PER_SEC << "秒" << endl;
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

這個作業使用了動態陣列儲存多項式的項（係數與指數），支援兩個多項式相加，合併同類項，實現多項式乘法，計算所有項的乘積並合併同類項，計算多項式在給定 x 值時的結果，支援格式化的多項式輸入與輸出。

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

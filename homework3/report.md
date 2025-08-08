# 41143231

作業三

## 解題說明


根據題目要求用環形鏈結串列作為底層儲存資料結構，使用的Chain和ChainNode類別儲存多項式的項（Term），每個項包含係數和指數，Polynomial類別支援多項式的輸入、輸出、加法、減法、乘法及在指定x值的求值功能，程式通過迭代器遍歷鏈結串列處理運算。



## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <cmath> 
using namespace std;

// 定義鏈結串列類別
template<class T>
class ChainNode;
class Polynomial;
class Term;

template<class T>
class Chain 
{
    friend ostream& operator<<(ostream& os, const Polynomial& x);
    friend Polynomial;
    friend ChainNode<T>;
public:
    // 建構函數，初始化鏈結串列
    Chain() 
    {
        first = &head;
        first->link = first;
        head.data.Set(-1, -1); // 設置頭節點為(-1, -1)
    }
    class ChainIterator {
    public:
        ChainIterator(ChainNode<T>* startNode = nullptr) 
        {
            current = startNode;
        }
        T& operator *() 
        {
            return current->data; // 返回當前節點
        }
        T* operator ->() 
        {
            return &current->data; // 返回當前節點的指針
        }
        ChainIterator& operator++() // 前置++
        {
            if (current)
                current = current->link; // 移動到下一個節點
            return *this;
        }
        ChainIterator operator++(int) // 後置++
        {
            ChainIterator old = *this;
            current = current->link; // 移動到下一個節點
            return old;
        }
        bool operator !=(const ChainIterator right) const
        {
            return current != right.current; // 比較當前節點是否不同
        }
        bool operator ==(const ChainIterator right) const
        {
            return current == right.current; // 比較當前節點是否相同
        }
    private:
        ChainNode<T>* current; // 當前節點
    };

    void Inserback(const T& item); // 在鏈結串列尾部插入項
    ChainIterator begin() const; 
    ChainIterator end() const; 

private:
    ChainNode<T>* first; // 指向頭節點
    ChainNode<T> head; // 頭節點
};

// 在鏈結串列尾部插入新節點
template<class T>
void Chain<T>::Inserback(const T& item)
{
    ChainNode<T>* current = first;
    while (current->link != first)
        current = current->link; // 找到尾節點
    current->link = new ChainNode<T>(item, first); // 插入新節點
}

template<class T>
typename Chain<T>::ChainIterator Chain<T>::begin() const
{
    return ChainIterator(first->link);
}

template<class T>
typename Chain<T>::ChainIterator Chain<T>::end() const 
{
    ChainNode<T>* current = first;
    do {
        if (current)
            return Chain<T>::ChainIterator(current);   
        current = current->link;
    } while (current->link != first);
    return ChainIterator(current);
}

// 鏈結串列節點類別
template<class T>
class ChainNode
{
    friend Term;
    friend Chain<T>;
public:
    ChainNode(); // 默認建構函數
    ChainNode(ChainNode<T>* link); // 指定鏈接的建構函數
    ChainNode(const T& data, ChainNode<T>* link); 
private:
    T data; // 節點
    ChainNode<T>* link; // 指向下一個節點
};

template<class T>
ChainNode<T>::ChainNode()
{
}

template<class T>
ChainNode<T>::ChainNode(ChainNode<T>*link)
{
    this->link = link;
}


template<class T>
ChainNode<T>::ChainNode(const T& data, ChainNode<T>* link)
{
    this->data = data;
    this->link = link;
}

// 多項式項類
class Term {
    friend Polynomial;
public:
    float coef; // 係數
    int exp; // 指數
    // 設置係數和指數
    Term Set(float c, int e)
    {
        coef = c;
        exp = e;
        return *this;
    }
};

// 多項式類
class Polynomial 
{
    friend Term;
    friend istream& operator>>(istream& is, Polynomial& x);
    friend ostream& operator<<(ostream& os, const Polynomial& x);
public:
    Polynomial() {} // 默認建構函數
    Polynomial(const Polynomial& a); // 複製建構函數
    ~Polynomial() {} // 析構函數
    Polynomial operator+(const Polynomial& b) const; // 加法運算
    Polynomial operator-(const Polynomial& b) const; // 減法運算
    Polynomial operator*(const Polynomial& b) const; // 乘法運算
    float Evaluate(float x) const; // 計算多項式在x處的值
private:
    Chain<Term> poly; // 儲存多項式項的鏈結串列
};

// 複製建構函數
Polynomial::Polynomial(const Polynomial& a) 
{
    poly = a.poly;
}

// 計算多項式在x處的值
float Polynomial::Evaluate(float x) const
{
    float result = 0;
    Chain<Term>::ChainIterator it = poly.begin();
    while (it != poly.end()) 
    { 
        result += it->coef * pow(x, it->exp); // 累加每項的值
        it++;
    }
    return result;
}

// 多項式加法
Polynomial Polynomial::operator+(const Polynomial& b) const
{
    Term temp;
    class Chain<Term>::ChainIterator ai = poly.begin();
    class Chain<Term>::ChainIterator bi = b.poly.begin();
    Polynomial c;
    while (ai->exp != -1 && bi->exp != -1)
    {
        if (ai->exp == bi->exp) 
        {
            int sum = ai->coef + bi->coef; // 同指數項係數相加
            if (sum)
                c.poly.Inserback(temp.Set(sum, ai->exp));
            ai++;
            bi++;
        }
        else if (ai->exp < bi->exp)
        {
            c.poly.Inserback(temp.Set(bi->coef, bi->exp)); // 插入b的多項式項
            bi++;
        }
        else {
            c.poly.Inserback(temp.Set(ai->coef, ai->exp)); // 插入a的多項式項
            ai++;
        }
    }
    return c;
}

// 多項式減法
Polynomial Polynomial::operator-(const Polynomial& b) const
{
    Term temp;
    class Chain<Term>::ChainIterator ai = poly.begin(), bi = b.poly.begin();
    Polynomial c;
    while (ai->exp != -1 && bi->exp != -1)
    {
        if (ai->exp == bi->exp) 
        {
            int sum = ai->coef - bi->coef; // 同指數項係數相減
            if (sum)
                c.poly.Inserback(temp.Set(sum, ai->exp));
            ai++;
            bi++;
        }
        else if (ai->exp < bi->exp)
        {
            c.poly.Inserback(temp.Set(-bi->coef, bi->exp)); // 插入b的負係數項
            bi++;
        }
        else 
        {
            c.poly.Inserback(temp.Set(ai->coef, ai->exp)); // 插入a的多項式項
            ai++;
        }
    }
    return c;
}

// 多項式乘法
Polynomial Polynomial::operator*(const Polynomial& b) const
{
    Term tmp;
    class Chain<Term>::ChainIterator ai = poly.begin(), bi = b.poly.begin();
    Polynomial Mult, ans;
    for (ai; ai->exp != -1; ai++)
    {
        for (bi; bi->exp != -1; bi++) {
            float cof = ai->coef * bi->coef; // 計算係數乘積
            int exp = ai->exp + bi->exp; // 計算指數和
            Mult.poly.Inserback(tmp.Set(cof, exp));
        }
    }
    class Chain<Term>::ChainIterator Mi = Mult.poly.begin(),i;
    for (Mi; Mi->exp != -1; Mi++) {
        float data = Mi->coef;
        for (i = Mi; i->exp != -1; i++) 
        {
            if (Mi->exp == i->exp)
            {
                data += i->coef; // 合併同指數項
                i->coef = 0;
            }
        }
        if (data)
            ans.poly.Inserback(tmp.Set(data, Mi->exp));
    }
    return ans;
}

// 輸入多項式
istream& operator>>(istream& is, Polynomial& x) 
{
    float coef;
    int exp;
    char c;
    Term tmp;
    while (1)
    {
        is >> coef; // 讀取係數
        c = getchar();
        c = getchar();
        is >> exp; // 讀取指數
        c = getchar();
        x.poly.Inserback(tmp.Set(coef, exp)); // 插入項
        if (c == '\n')
            break; // 遇到換行結束
    }
    return is;
}

// 輸出多項式
ostream& operator<<(ostream& os, const Polynomial& x)
{
    class Chain<Term>::ChainIterator first = x.poly.begin();
    class Chain<Term>::ChainIterator end = x.poly.end();
    for (; first != end; first++) 
    {
        if (first->exp == 0) {
            os << first->coef; // 常數項直接輸出
            continue;
        }
        os << first->coef << "X^" << first->exp << "+"; // 輸出帶指數的項
    }
    return os;
}

// 主函數
int main(){
    Polynomial poly1, poly2, poly3;
    int x;
    cout << "輸入第一個多項式數據:"; // 提示輸入第一個多項式
    cin >> poly1;
    cout << "輸入第二個多項式數據:"; // 提示輸入第二個多項式
    cin >> poly2;
    cout << "輸入x值用於計算多項式:"; // 提示輸入x值
    cin >> x;
    clock_t start = clock(); // 記錄開始時間
    cout << "poly1 在 x=" << x << " 的值= " << poly1.Evaluate(x) << endl; // 計算並輸出poly1的值
    cout << "poly2 在 x=" << x << " 的值= " << poly2.Evaluate(x) << endl; // 計算並輸出poly2的值
    poly3 = poly1 + poly2;
    cout << "poly1 + poly2 = " << poly3 << endl; // 輸出加法結果
    poly3 = poly1 - poly2;
    cout << "poly1 - poly2 = " << poly3 << endl; // 輸出減法結果
    poly3 = poly1 * poly2;
    cout << "poly1 * poly2 = " << poly3 << endl; // 輸出乘法結果
    clock_t stop = clock(); // 記錄結束時間
    cout << "花費時間：" << double(stop - start) / CLOCKS_PER_SEC << "秒" << endl; // 輸出運行時間
    return 0;
}
```

## 效能分析

|      | 時間複雜度 | 空間複雜度 |
|----------|--------------|----------|
| 加法   | $O（m + n）$      | $m + n$         |
| 乘法   | $O（m * n + x^2）$      | $x$          |
| 減法   | $O（m+n）$      |  $m+n$         |
| 取值   | $O（m）$      |  $1$        |
| 輸入   | $O（y）$     |  $1$  |
| 輸出   | $O（z）$     |  $1$  |

## 測試與驗證

### 測試案例

1

    p1: (4X^2+2X^1+2X^0)
  
    P2: (2X^2+2X^1+2X^0)
  
    代入數字:3

![hw_3](https://github.com/Adsgfjhk/data-structure/blob/main/homework3/%E8%9E%A2%E5%B9%95%E6%93%B7%E5%8F%96%E7%95%AB%E9%9D%A2%202025-08-08%20204243.png)



### 結論

這個作業使用鏈結串列的多項式運算系統，能夠執行多項式的輸入、加法、減法、乘法以及在特定點的求值操作。透過模板化的 Chain和 ChainNode，程式以鏈結串列儲存多項式項，並利用迭代器遍歷操作，Polynomial提供了多項式的基本運算，包括加法 (operator+)、減法 (operator-) 和乘法 (operator*)，並支援在指定 x 值處計算多項式值 (Evaluate)。輸入輸出操作透過重載的 >> 和 << 運算子實現，方便輸入多項式係數與指數，並輸出結果。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用鏈結串列的原因如下：

1. **動態記憶體分配**  
   鏈結串列允許動態插入與刪除節點，適合多項式項數量不固定的場景，而與陣列相比，鏈結串列無需預先指定大小，能根據輸入動態調整，節省記憶體並提高靈活性。

2. **靈活的遍歷與修改**
   鏈結串列透過迭代器（ChainIterator）支援順序遍歷，方便實現多項式的加、減、乘等運算，修改節點（如合併同類項）只需調整指針，無需像陣列般移動大量數據。
3. **適應稀疏多項式（Sparse Polynomial）**  
   多項式可能包含許多零係數項 $（如  x^{100} + x^2 $），鏈結串列只需儲存非零項，節省記憶體，而陣列需要為每個指數分配空間，導致浪費。

4. **高效插入**  
   多項式運算（如加法、減法）需要按指數順序插入或合併項，鏈結串列的插入操作（特別是在尾部）時間複雜度為 O(1)（若已知尾節點），比陣列的插入（需移動元素，O(n)）更高效。
     
鏈結串列因其動態性、高效插入與適應稀疏多項式（Sparse Polynomial）的特性，非常適合多項式運算系統的需求，尤其在項數量不確定或需要頻繁插入的情況下，提供了高效且靈活的解法。


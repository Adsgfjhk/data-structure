#include <iostream>
#include <cstdio>
#include <cmath> 
using namespace std;

class Polynomial; 

// Term 類，用於表示多項式中的單項
class Term {
    friend Polynomial; 
    friend ostream& operator<<(ostream& os, const Polynomial& p); // 用於輸出
    friend istream& operator>>(istream& in, Polynomial& p); // 用於輸入
private:
    float coef; // 係數
    int exp;    // 指數
};

// Polynomial 類，用於表示多項式
class Polynomial {
    friend ostream& operator<<(ostream& os, const Polynomial& p); // 用於輸出多項式
    friend istream& operator>>(istream& input, Polynomial& p);   // 用於輸入多項式
private:
    Term* termArray; // 儲存多項式非零項的動態陣列
    int capacity;    // termArray 的大小（容量）
    int terms;       // 非零項的數量
public:
    Polynomial(); // 建構函數，初始化為零多項式
    Polynomial Add(Polynomial poly); // 返回當前多項式與另一多項式的和
    Polynomial Mult(Polynomial poly); // 返回當前多項式與另一多項式的積
    void NewTerm(const int newCoef, const int newExp); // 新增一項到多項式
    float Eval(float f); // 計算多項式在指定值 f 的結果
};

// 建構函數，初始化多項式
Polynomial::Polynomial() : capacity(2), terms(0) {
    termArray = new Term[capacity]; // 分配初始容量為 2 的動態陣列
}

// 新增一項到多項式
void Polynomial::NewTerm(const int newCoef, const int newExp) {
    if (terms == capacity) { // 若陣列空間不足，擴充容量
        capacity *= 2; // 容量加倍
        Term* temp = new Term[capacity]; // 創建新的更大陣列
        copy(termArray, termArray + terms, temp); // 複製現有項到新陣列
        delete[] termArray; // 釋放舊陣列
        termArray = temp; // 更新指向新陣列
    }
    termArray[terms].coef = newCoef; // 設定新項的係數
    termArray[terms++].exp = newExp; // 設定新項的指數並增加項數
}

// 計算多項式在給定值 x 的結果
float Polynomial::Eval(float value) {
    float result = 0;
    // 對每個項計算：係數 * value^指數
    for (int i = 0; i < terms; i++) { // 修正：使用 terms 而非 termCount
        result += termArray[i].coef * pow(value, termArray[i].exp);
    }
    return result;
}

// 多項式加法
Polynomial Polynomial::Add(Polynomial other) {
    Polynomial result; // 結果多項式
    int thisIndex = 0, otherIndex = 0;

    // 根據指數合併兩個多項式的項
    while (thisIndex < terms && otherIndex < other.terms) {
        if (termArray[thisIndex].exp == other.termArray[otherIndex].exp) {
            // 相同指數：係數相加
            float sum = termArray[thisIndex].coef + other.termArray[otherIndex].coef;
            if (sum != 0) // 若係數和不為零，新增到結果
                result.NewTerm(sum, termArray[thisIndex].exp);
            thisIndex++;
            otherIndex++;
        } else if (termArray[thisIndex].exp < other.termArray[otherIndex].exp) {
            // 複製另一多項式的項
            result.NewTerm(other.termArray[otherIndex].coef, other.termArray[otherIndex].exp);
            otherIndex++;
        } else {
            // 複製當前多項式的項
            result.NewTerm(termArray[thisIndex].coef, termArray[thisIndex].exp);
            thisIndex++;
        }
    }
    // 複製當前多項式剩餘的項
    for (; thisIndex < terms; thisIndex++) {
        result.NewTerm(termArray[thisIndex].coef, termArray[thisIndex].exp);
    }
    // 複 Old: 複製另一多項式剩餘的項
    for (; otherIndex < other.terms; otherIndex++) {
        result.NewTerm(other.termArray[otherIndex].coef, other.termArray[otherIndex].exp);
    }
    return result;
}

// 重載輸出運算子，用於輸出多項式
ostream& operator<<(ostream& os, const Polynomial& p) {
    for (int i = 0; i < p.terms; i++) {
        if (p.termArray[i].exp == 0) { // 若為常數項，只輸出係數
            os << p.termArray[i].coef;
            continue;
        }
        if (i == p.terms - 1) { // 最後一項，不加 "+"
            os << p.termArray[i].coef << "X^" << p.termArray[i].exp;
        } else { // 非最後一項，加 "+"
            os << p.termArray[i].coef << "X^" << p.termArray[i].exp << "+";
        }
    }
    return os;
}

// 重載輸入運算子，用於輸入多項式
istream& operator>>(istream& in, Polynomial& p) {
    int x, y;
    char c;
    while (true) {
        in >> x; // 讀取係數
        c = getchar(); // 讀取並丟棄 'X' 字符
        c = getchar(); // 讀取並丟棄 '^' 字符
        in >> y; // 讀取指數
        c = getchar(); // 讀取並檢查是否為 '+' 或換行
        p.NewTerm(x, y); // 將輸入的係數和指數新增到多項式
        if (c == '\n') break; // 若讀到換行，結束輸入
    }
    return in;
}

// 多項式乘法
Polynomial Polynomial::Mult(Polynomial poly) {
    Polynomial ans, num; // ans 儲存中間結果，num 儲存最終結果
    int* ch = new int[ans.terms]; // 用於記錄已處理的指數
    int check;

    // 計算所有項的乘積
    for (int i = 0; i < terms; i++) { // 走訪當前多項式的項
        for (int j = 0; j < poly.terms; j++) { // 走訪參數多項式的項
            // 係數相乘，指數相加
            ans.NewTerm(termArray[i].coef * poly.termArray[j].coef, termArray[i].exp + poly.termArray[j].exp);
        }
    }

    // 初始化檢查陣列
    for (int d = 0; d < ans.terms; d++)
        ch[d] = 0;

    // 合併同類項
    for (int i = 0; i < ans.terms; i++) {
        float total = 0;
        int f = 1;
        check = 1;
        if (ans.termArray[i].exp == 0) { // 若為常數項，直接新增
            num.NewTerm(ans.termArray[i].coef, ans.termArray[i].exp);
            break;
        }
        // 計算相同指數的係數和
        for (int j = i + 1; j < ans.terms; j++) {
            if (ans.termArray[i].exp == ans.termArray[j].exp && f) {
                total += ans.termArray[i].coef + ans.termArray[j].coef;
                f = 0;
            } else if (ans.termArray[i].exp == ans.termArray[j].exp) {
                total += ans.termArray[j].coef;
            }
        }
        // 檢查指數是否已處理
        for (int c = 0; c < ans.terms; c++) {
            if (ans.termArray[i].exp == ch[c]) {
                check = 0;
                break;
            }
        }
        // 若有同類項，新增合併後的係數
        if (total) {
            if (check)
                num.NewTerm(total, ans.termArray[i].exp);
        } else {
            if (check)
                num.NewTerm(ans.termArray[i].coef, ans.termArray[i].exp);
        }
        ch[i] = ans.termArray[i].exp; // 記錄已處理的指數
    }
    delete[] ch; // 釋放動態陣列
    return num; // 返回最終結果
}

// 主函數
int main() {
    Polynomial p1, p2; // 創建兩個多項式對象
    int x;
    cout << "請輸入第一個多項式"; // 提示輸入第一個多項式
    cin >> p1; // 輸入第一個多項式
    cout << "請輸入第二個多項式"; // 提示輸入第二個多項式
    cin >> p2; // 輸入第二個多項式
    cout << "請輸入X的值"; // 提示輸入 x 值
    cin >> x; // 讀取 x 值
    clock_t start = clock(); // 計時開始
    cout << "p1.Eval(x)    = " << p1.Eval(x) << endl; // 計算並輸出 p1 在 x 的值
    cout << "p2.Eval(x)    = " << p2.Eval(x) << endl; // 計算並輸出 p2 在 x 的值
    cout << "p1.Add(p2)    = " << p1.Add(p2) << endl; // 計算並輸出 p1 + p2
    cout << "p1.Mult(p2)   = " << p1.Mult(p2) << endl; // 計算並輸出 p1 * p2
    clock_t stop = clock(); // 計時結束
    cout << "花費時間：" << double(stop - start) / CLOCKS_PER_SEC << "秒" << endl; // 輸出執行時間
    return 0;
}

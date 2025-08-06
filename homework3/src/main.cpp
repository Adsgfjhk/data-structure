#include <iostream>
#include <cmath> 
using namespace std;

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
    Chain() 
    {
        first = &head;
        first->link = first;
        head.data.Set(-1, -1);
    }
    class ChainIterator {
    public:
        ChainIterator(ChainNode<T>* startNode = nullptr) 
        {
            current = startNode;
        }
        T& operator *() 
        {
            return current->data;
        }
        T* operator ->() 
        {
            return &current->data;
        }
        ChainIterator& operator++()
        {
            if (current)
                current = current->link;
            return *this;
        }
        ChainIterator operator++(int) 
        {
            ChainIterator old = *this;
            current = current->link;
            return old;
        }
        bool operator !=(const ChainIterator right) const
        {
            return current != right.current;
        }
        bool operator ==(const ChainIterator right) const
        {
            return current == right.current;
        }
    private:
        ChainNode<T>* current;
    };

    void Inserback(const T& item);
    ChainIterator begin() const;
    ChainIterator end() const;

private:
    ChainNode<T>* first;
    ChainNode<T> head;
};

template<class T>
void Chain<T>::Inserback(const T& item)
{
    ChainNode<T>* current = first;
    while (current->link != first)
        current = current->link;
    current->link = new ChainNode<T>(item, first);
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

template<class T>
class ChainNode
{
    friend Term;
    friend Chain<T>;
public:
    ChainNode();
    ChainNode(ChainNode<T>* link);
    ChainNode(const T& data, ChainNode<T>* link);
private:
    T data;
    ChainNode<T>* link;
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
class Term {
    friend Polynomial;
public:
    float coef;
    int exp;
    Term Set(float c, int e)
    {
        coef = c;
        exp = e;
        return *this;
    }
};

class Polynomial 
{
    friend Term;
    friend istream& operator>>(istream& is, Polynomial& x);
    friend ostream& operator<<(ostream& os, const Polynomial& x);
public:
    Polynomial() {}
    Polynomial(const Polynomial& a);
    ~Polynomial() {}
    Polynomial operator+(const Polynomial& b) const;
    Polynomial operator-(const Polynomial& b) const;
    Polynomial operator*(const Polynomial& b) const;
    float Evaluate(float x) const; // Added Evaluate method
private:
    Chain<Term> poly;
};

Polynomial::Polynomial(const Polynomial& a) 
{
    poly = a.poly;
}

float Polynomial::Evaluate(float x) const
{
    float result = 0;
    Chain<Term>::ChainIterator it = poly.begin();
    while (it != poly.end()) 
    { 
        result += it->coef * pow(x, it->exp);
        it++;
    }
    return result;
}

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
            int sum = ai->coef + bi->coef;
            if (sum)
                c.poly.Inserback(temp.Set(sum, ai->exp));
            ai++;
            bi++;
        }
        else if (ai->exp < bi->exp)
        {
            c.poly.Inserback(temp.Set(bi->coef, bi->exp));
            bi++;
        }
        else {
            c.poly.Inserback(temp.Set(ai->coef, ai->exp));
            ai++;
        }
    }
    return c;
}

Polynomial Polynomial::operator-(const Polynomial& b) const
{
    Term temp;
   class Chain<Term>::ChainIterator ai = poly.begin(), bi = b.poly.begin();
    Polynomial c;
    while (ai->exp != -1 && bi->exp != -1)
    {
        if (ai->exp == bi->exp) 
        {
            int sum = ai->coef - bi->coef;
            if (sum)
                c.poly.Inserback(temp.Set(sum, ai->exp));
            ai++;
            bi++;
        }
        else if (ai->exp < bi->exp)
        {
            c.poly.Inserback(temp.Set(-bi->coef, bi->exp));
            bi++;
        }
        else 
        {
            c.poly.Inserback(temp.Set(ai->coef, ai->exp));
            ai++;
        }
    }
    return c;
}

Polynomial Polynomial::operator*(const Polynomial& b) const
{
    Term tmp;
   class Chain<Term>::ChainIterator ai = poly.begin(), bi = poly.begin();
    Polynomial Mult, ans;
    for (ai; ai->exp != -1; ai++)
    {
        for (bi; bi->exp != -1; bi++) {
            float cof = ai->coef * bi->coef;
            int exp = ai->exp + bi->exp;
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
                data += i->coef;
                i->coef = 0;
            }
        }
        if (data)
            ans.poly.Inserback(tmp.Set(data, Mi->exp));
    }
    return ans;
}

istream& operator>>(istream& is, Polynomial& x) 
{
    float coef;
    int exp;
    char c;
    Term tmp;
    while (1)
    {
        is >> coef;
        c = getchar();
        c = getchar();
        is >> exp;
        c = getchar();
        x.poly.Inserback(tmp.Set(coef, exp));
        if (c == '\n')
            break;
    }
    return is;
}

ostream& operator<<(ostream& os, const Polynomial& x)
{
  class  Chain<Term>::ChainIterator first = x.poly.begin();
  class  Chain<Term>::ChainIterator end = x.poly.end();
    for (; first != end; first++) 
    {
        if (first->exp == 0) {
            os << first->coef;
            continue;
        }
        os << first->coef << "X^" << first->exp << "+";
    }
    return os;
}

int main(){
    Polynomial poly1, poly2, poly3;
    int x;
    cout << "input poly1 data:";
    cin >> poly1;
    cout << "input poly2 data:";
    cin >> poly2;
    cout << "poly Eval x =";
    cin >> x;
    clock_t start = clock();
    cout << "poly1.Evaluate(x)= " << poly1.Evaluate(x) << endl;
    cout << "poly2.Evaluate(x)= " << poly2.Evaluate(x) << endl;
    poly3 = poly1 + poly2;
    cout << "poly1 + poly2 = " << poly3 << endl;
    poly3 = poly1 - poly2;
    cout << "poly1 - poly2 = " << poly3 << endl;
    poly3 = poly1 * poly2;
    cout << "poly1 * poly2 = " << poly3 << endl;
    clock_t stop = clock();
    cout << "花費時間：" << double(stop - start) / CLOCKS_PER_SEC << "秒" << endl;
    return 0;
}

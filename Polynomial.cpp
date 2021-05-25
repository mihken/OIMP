#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <cmath>

using namespace std;

template<typename T>
T Pow(const T &t, int n) {
    if (n == 0) {
        return T(1);
    }
    T ans = T(1);
    for (int i = 0; i < n; ++i) {
        ans *= t;
    }
    return ans;
}

template<typename T>

class Polynomial {
private:
    vector<T> P;

public:
    void Normalize() {
        while (!P.empty() && P.back() == T(0)) {
            P.pop_back();
        }
    }

    Polynomial(const vector<T> &v) : P(v) {
        Normalize();
    }

    Polynomial(T t = T()) : P{t} {
        Normalize();
    }

    typename vector<T>::const_iterator begin() const {
        return P.begin();
    }

    typename vector<T>::iterator begin() {
        return P.begin();
    }

    typename vector<T>::iterator end() {
        return P.end();
    }

    typename vector<T>::const_iterator end() const {
        return P.end();
    }

    template<typename Iterator>
    Polynomial(Iterator begin, Iterator end): P(begin, end) {
        Normalize();
    }

    bool operator==(const Polynomial &other) const {
        return P == other.P;
    }

    bool operator!=(const Polynomial &other) const {
        return P != other.P;
    }

    Polynomial &operator+=(const Polynomial &other) {
        for (size_t i = 0; i < P.size() && i < other.P.size(); ++i) {
            P[i] += other.P[i];
        }
        for (size_t i = P.size(); i < other.P.size(); ++i) {
            P.push_back(other.P[i]);
        }
        Normalize();
        return *this;
    }

    Polynomial operator+(const Polynomial &other) const {
        Polynomial temp(P);
        temp += other;
        return temp;
    }

    Polynomial &operator-=(const Polynomial &other) {
        for (size_t i = 0; i < P.size() && i < other.P.size(); ++i) {
            P[i] -= other.P[i];
        }
        for (size_t i = P.size(); i < other.P.size(); ++i) {
            P.push_back(-other.P[i]);
        }
        Normalize();
        return *this;
    }

    Polynomial operator-(const Polynomial &other) const {
        Polynomial temp(P);
        temp -= other;
        return temp;
    }

    int Degree() const {
        int ans = P.size() - 1;
        return ans;
    }

    const T operator[](const size_t n) const {
        if (n > P.size()) {
            return T(0);
        } else {
            return P[n];
        }
    }

    Polynomial operator*(const Polynomial &other) const {
        if (other.P.empty() || P.empty()) {
            return Polynomial(T(0));
        }
        Polynomial<T> temp(T(0));
        temp.P.resize(Degree() + other.Degree() + 1, T(0));
        for (int i = 0; i <= Degree(); ++i) {
            for (int j = 0; j <= other.Degree(); ++j) {
                temp.P[i + j] += (*this)[i] * other[j];
            }
        }
        temp.Normalize();
        return temp;
    }

    Polynomial &operator*=(const Polynomial &other) {
        *this = *this * other;
        Normalize();
        return *this;
    }

    T operator()(const T &x) const {
        T ans = T(0);
        int n = P.size();
        for (int i = 0; i < n; ++i) {
            ans += Pow(x, i) * P[i];
        }
        return ans;
    }

    Polynomial operator&(const Polynomial &other) const {
        if (other.P.empty() || P.empty()) {
            return Polynomial(T(0));
        }
        Polynomial<T> ans(T(0));
        ans.P.resize(Degree() * other.Degree() + 1, T(0));
        Polynomial<T> temp(T(1));
        for (int i = 0; i <= Degree(); ++i) {
            ans += (temp * Polynomial(P[i]));
            temp *= other;
        }
        ans.Normalize();
        return ans;
    }

    Polynomial operator/(const Polynomial &other) const {
        Polynomial ans(T(0));
        Polynomial temp(*this);
        while (temp.Degree() >= other.Degree()) {
            int dDegree = temp.Degree() - other.Degree();
            std::vector<T> parent(dDegree + 1, T(0));
            parent[dDegree] = temp[temp.Degree()] / other[other.Degree()];
            Polynomial q(parent);
            ans += q;
            temp -= q * other;
            temp.Normalize();

        }
        ans.Normalize();
        return ans;
    }

    Polynomial operator%(const Polynomial& other) const {
        auto ans = *this - (*this / other) * other;
        ans.Normalize();
        return ans;
    }



    template<typename U>
    friend ostream &operator<<(ostream &, const Polynomial<U> &);
};

template<typename T>
ostream &operator<<(ostream &out, const Polynomial<T> &p) {
    if (p.Degree() == -1) {
        out << "0";
        return out;
    }

    for (int i = p.Degree(); i >= 0; --i) {
        if (p[i] == T(0)) {
            continue;
        }
        if (i == 0) {
            if (p[i] > T(0) && i != p.Degree()) {
                out << "+" << p[i];
            } else {
                out << p[i];
            }
            continue;
        }
        if (p[i] < T(0)) {
            if (-p[i] == T(1)) {
                cout << "-";
            } else {
                out << p[i] << "*";
            }
        }
        if (p[i] > T(0)) {
            if (i != p.Degree()) {
                out << "+";
            }
            if (p[i] != T(1)) {
                out << p[i] << "*";
            }
        }
        out << "x";
        if (i != 1) {
            out << "^" << i;
        }
    }
    return out;
}


int main() {
    vector<int> v = {1, 2, 3, 4};
    Polynomial<int> a(v);
    vector<int> g = {1, 2};
    Polynomial<int> b(g);
    //cout << (a *= b) << "\n";
    //cout << a(1);
    cout << a / b;
    // cout << a.Degree();
    //cout << a[3];
    //cout << (a & b);
    return 0;
}

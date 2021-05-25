#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Matrix {
    vector<vector<T>> v;
public:
    Matrix(const vector<vector<T>> &v) : v(v) {}

    pair<size_t, size_t> size() const {
        return {v.size(), v[0].size()};
    }

    template<typename U>
    friend ostream &operator<<(ostream &out, const Matrix<U> &m);

};

template<typename U>
ostream &operator<<(ostream &out, const Matrix<U> &m) {
    auto[h, w] = m.size();

    for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            out << m.v[i][j];
            if (j != w - 1)
                out << '\t';
        }
        if (i != h - 1)
            out << '\n';
    }

    return out;
}

int main() {

    cout << '(' << Matrix<int>({{1,  1},
                                {2,  3},
                                {-1, 0}}) << ')' << '\n';
    cout << '(' << Matrix<int>({{1,  10},
                                {2,  3},
                                {-1, 0},
                                {7,  9}}) << ')' << '\n';
    cout << '(' << Matrix<int>({{1, 2, 3, 4, 5, 6}}) << ')' << '\n';
    cout << '(' << Matrix<int>({{7, 8, 9, 10}}) << ')' << '\n';
    cout << '(' << Matrix<int>({{7},
                                {8},
                                {9},
                                {10}}) << ')' << '\n';
    cout << '(' << Matrix<int>(vector<vector<int>>{{7}}) << ')' << '\n';

}

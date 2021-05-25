#include <iostream>
#include <vector>

template <typename T>
class MathVector {
private:
    std::vector<T> data;

public:
    // Zero vector of size n
    MathVector(size_t n) {
        data.resize(n);
    }

    template <typename Iter>
    MathVector(Iter first, Iter last) {
        while (first != last) {
            data.push_back(*first);
            ++first;
        }
    }

    size_t Dimension() const {
        return data.size();
    }
    T& operator[](size_t i) {
        return data[i];
    }
    const T& operator[](size_t i) const {
        return data[i];
    }
};


// Output format: (1, 2, 3, 4, 5)
template <typename T>
std::ostream& operator << (std::ostream& out, const MathVector<T>& v) {
    out << '(';
    for (size_t i = 0; i != v.Dimension(); ++i) {
        if (i > 0)
            out << ", ";
        out << v[i];
    }
    out << ')';
    return out;
}

template <typename T>
MathVector<T>& operator *= (MathVector<T>& v, const T& scalar) {
    for (size_t i = 0; i != v.Dimension(); ++i)
        v[i] *= scalar;
    return v;
}

template <typename T>
MathVector<T> operator * (const MathVector<T>& v, const T& scalar) {
    MathVector<T> temp(v);
    temp *= scalar;
    return temp;
}

template <typename T>
MathVector<T> operator * (T scalar, const MathVector<T>& v) {
    return v * scalar;
}


template <typename T>
MathVector<T>& operator += (MathVector<T>& v, const MathVector<T>& v1) {
    for (size_t i = 0; i != v.Dimension(); ++i)
        v[i] += v1[i];
    return v;
}

template <typename T>
MathVector<T> operator + (const MathVector<T>& v, const MathVector<T>& v1) {
    auto temp(v);
    temp += v1;
    return temp;
}
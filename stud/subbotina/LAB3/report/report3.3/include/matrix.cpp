#include <exception>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <utility>


template<class T>
std::vector<T> operator + (const std::vector<T>& a, const std::vector<T>& b) {
    size_t n = a.size();
    std::vector<T> c(n);
    for (size_t i = 0; i < n; ++i) {
        c[i] = a[i] + b[i];
    }
    return c;
}

template<class T>
std::vector<T> operator - (const std::vector<T>& a, const std::vector<T>& b) {
    size_t n = a.size();
    std::vector<T> c(n);
    for (size_t i = 0; i < n; ++i) {
        c[i] = a[i] - b[i];
    }
    return c;
}

template<class T>
class Matrix {
private:
    using matrix = Matrix<T>;
    using vec = std::vector<T>;

    size_t n, m;
    std::vector<vec> data;
public:
    Matrix() : n(1), m(1), data(1) {}

    Matrix(size_t _n) : n(_n), m(_n) {
        data.resize(n, vec(n));
    }

    Matrix(size_t _n, size_t _m) : n(_n), m(_m) {
        data.resize(n, vec(m));
    }

    Matrix(const matrix& other) {
        n = other.n;
        m = other.m;
        data = other.data;
    }

    matrix& operator = (const matrix& other) {
        if (this == &other) {
            return *this;
        }
        n = other.n;
        m = other.m;
        data = other.data;
        return *this;
    }

    static matrix identity(size_t n) {
        matrix res(n, n);
        for (size_t i = 0; i < n; ++i) {
            res[i][i] = T(1);
        }
        return res;
    }

    size_t rows() const {
        return n;
    }

    size_t cols() const {
        return m;
    }

    void swap_rows(size_t i, size_t j) {
        if (i == j) {
            return;
        }
        for (size_t k = 0; k < m; ++k) {
            std::swap(data[i][k], data[j][k]);
        }
    }

    void swap_cols(size_t i, size_t j) {
        if (i == j) {
            return;
        }
        for (size_t k = 0; k < n; ++k) {
            std::swap(data[k][i], data[k][j]);
        }
    }

    matrix t() const {
        Matrix<T> res(m, n);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                res[j][i] = data[i][j];
            }
        }
        return res;
    }

    friend matrix operator + (const matrix& a, const matrix& b) {
        if (a.rows() != b.rows() or a.cols() != b.cols()) {
            throw std::invalid_argument("Sizes does not match");
        }
        size_t n = a.rows();
        size_t m = a.cols();
        matrix res(n, m);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                res[i][j] = a[i][j] + b[i][j];
            }
        }
        return res;
    }

    friend matrix operator - (const matrix& a, const matrix& b) {
        if (a.rows() != b.rows() or a.cols() != b.cols()) {
            throw std::invalid_argument("Sizes does not match");
        }
        size_t n = a.rows();
        size_t m = a.cols();
        matrix res(n, m);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                res[i][j] = a[i][j] - b[i][j];
            }
        }
        return res;
    }

    friend matrix operator * (T lambda, const matrix& a) {
        size_t n = a.rows();
        size_t m = a.cols();
        matrix res(n, m);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                res[i][j] = lambda * a[i][j];
            }
        }
        return res;
    }

    friend vec operator * (const matrix& a, const vec& b) {
        if (a.cols() != b.size()) {
            throw std::invalid_argument("Sizes does not match");
        }
        size_t n = a.rows();
        size_t m = a.cols();
        vec c(n);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                c[i] += a[i][j] * b[j];
            }
        }
        return c;
    }

    friend matrix operator * (const matrix& a, const matrix& b) {
        if (a.cols() != b.rows()) {
            throw std::invalid_argument("Sizes does not match");
        }
        size_t n = a.rows();
        size_t k = a.cols();
        size_t m = b.cols();
        matrix res(n, m);
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                for (size_t ii = 0; ii < k; ++ii) {
                    res[i][j] += a[i][ii] * b[ii][j];
                }
            }
        }
        return res;
    }

    vec& operator [] (size_t i) {
        return data[i];
    }

    const vec& operator [] (size_t i) const {
        return data[i];
    }

    friend std::ostream& operator << (std::ostream& out, const matrix& matr) {
        for (size_t i = 0; i < matr.rows(); ++i) {
            for (size_t j = 0; j < matr.cols(); ++j) {
                if (j) {
                    out << ", ";
                }
                out << matr[i][j];
            }
            out << '\n';
        }
        return out;
    }

    friend std::istream& operator >> (std::istream& in, matrix& matr) {
        for (size_t i = 0; i < matr.rows(); ++i) {
            for (size_t j = 0; j < matr.cols(); ++j) {
                in >> matr[i][j];
            }
        }
        return in;
    }

    ~Matrix() = default;
};

template<class T>
class LU {
private:
    using matrix = Matrix<T>;
    using vec = std::vector<T>;
    using pii = std::pair<size_t, size_t>;

    const T EPS = 1e-6;

    matrix l;
    matrix u;
    T det;
    std::vector<pii> swaps;

    void decompose() {
        size_t n = u.rows();
        for (size_t i = 0; i < n; ++i) {
            size_t max_el_ind = i;
            for (size_t j = i + 1; j < n; ++j) {
                if (abs(u[j][i]) > abs(u[max_el_ind][i])) {
                    max_el_ind = j;
                }
            }
            if (max_el_ind != i) {
                pii perm = std::make_pair(i, max_el_ind);
                swaps.push_back(perm);
                u.swap_rows(i, max_el_ind);
                l.swap_rows(i, max_el_ind);
                l.swap_cols(i, max_el_ind);
            }
            for (size_t j = i + 1; j < n; ++j) {
                if (abs(u[i][i]) < EPS) {
                    continue;
                }
                T mu = u[j][i] / u[i][i];
                l[j][i] = mu;
                for (size_t k = 0; k < n; ++k) {
                    u[j][k] -= mu * u[i][k];
                }
            }
        }
        det = (swaps.size() & 1 ? -1 : 1);
        for (size_t i = 0; i < n; ++i) {
            det *= u[i][i];
        }
    }

    void do_swaps(vec& x) {
        for (pii elem : swaps) {
            std::swap(x[elem.first], x[elem.second]);
        }
    }
public:
    LU(const matrix& matr) {
        if (matr.rows() != matr.cols()) {
            throw std::invalid_argument("Matrix is not square");
        }
        l = matrix::identity(matr.rows());
        u = matrix(matr);
        decompose();
    }

    friend std::ostream& operator << (std::ostream& out, const LU<T>& lu) {
        out << "Matrix L:\n" << lu.l << "Matrix U:\n" << lu.u;
        return out;
    }

    T get_det() {
        return det;
    }

    vec solve(vec b) {
        int n = b.size();
        do_swaps(b);
        vec z(n);
        for (int i = 0; i < n; ++i) {
            T summary = b[i];
            for (int j = 0; j < i; ++j) {
                summary -= z[j] * l[i][j];
            }
            z[i] = summary;
        }
        vec x(n);
        for (int i = n - 1; i >= 0; --i) {
            if (abs(u[i][i]) < EPS) {
                continue;
            }
            T summary = z[i];
            for (int j = n - 1; j > i; --j) {
                summary -= x[j] * u[i][j];
            }
            x[i] = summary / u[i][i];
        }
        return x;
    }

    matrix inv_matrix() {
        size_t n = l.rows();
        matrix res(n);
        for (size_t i = 0; i < n; ++i) {
            vec b(n);
            b[i] = T(1);
            vec x = solve(b);
            for (size_t j = 0; j < n; ++j) {
                res[j][i] = x[j];
            }
        }
        return res;
    }

    ~LU() = default;
};

#include <iostream>
#include <vector>

using namespace std;

vector<double> solveTridiagonalMatrix(vector<double> a, vector<double> b, vector<double> c, vector<double> d) {
    int n = d.size();

    vector<double> alpha(n), beta(n), x(n);
    alpha[0] = -c[0] / b[0];
    beta[0] = d[0] / b[0];

    for (int i = 1; i < n; ++i) {
        double m = 1.0 / (b[i] + a[i] * alpha[i - 1]);
        alpha[i] = -c[i] * m;
        beta[i] = (d[i] - a[i] * beta[i - 1]) * m;
    }

    x[n - 1] = beta[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        x[i] = alpha[i] * x[i + 1] + beta[i];
    }

    return x;
}

int main() {
    vector<vector<double>> A = { {16, -9, 0, 0, 0},
                                 {8, -13, -5, 0, 0},
                                 {0, -3, -21, 9, 0},
                                 {0, 0, -9, 16, -5},
                                 {0, 0, 0, 1, -9} };

    vector<double> b = { -27, -84, -225, -89, 69 };

    // Извлекаем элементы из матрицы A для прогонки
    vector<double> a, c, d;
    vector<double> main_diag;
    for (int i = 0; i < A.size(); ++i) {
        main_diag.push_back(A[i][i]);
        if (i > 0) {
            a.push_back(A[i][i - 1]);
        }
        if (i < A.size() - 1) {
            c.push_back(A[i][i + 1]);
        }
    }

    d = b;

    vector<double> result = solveTridiagonalMatrix(a, main_diag, c, d);

    cout << "Решение СЛАУ:" << endl;
    for (int i = 0; i < result.size(); ++i) {
        cout << "x[" << i << "] = " << result[i] << endl;
    }

    return 0;
}
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

const double EPS = 1e-10;

vector<vector<double>> matrixMultiply(const vector<vector<double>>& A, const vector<vector<double>>& B) {
    int n = A.size();
    int m = B[0].size();
    vector<vector<double>> C(n, vector<double>(m, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int k = 0; k < B.size(); ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Функция для вычисления QR-разложения матрицы
void qrDecomposition(const vector<vector<double>>& A, vector<vector<double>>& Q, vector<vector<double>>& R) {
    int n = A.size();
    Q = R = vector<vector<double>>(n, vector<double>(n));

    for (int j = 0; j < n; ++j) {
        vector<double> v(n);
        for (int i = 0; i < j; ++i) {
            double dotProduct = 0;
            for (int k = 0; k < n; ++k) {
                dotProduct += Q[k][i] * A[k][j];
            }
            for (int k = 0; k < n; ++k) {
                v[k] += dotProduct * Q[k][i];
            }
        }

        double norm = 0;
        for (int i = 0; i < n; ++i) {
            v[i] = A[i][j] - v[i];
            norm += v[i] * v[i];
        }
        norm = sqrt(norm);

        for (int i = 0; i < n; ++i) {
            Q[i][j] = v[i] / norm;
        }

        for (int i = 0; i <= j; ++i) {
            R[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                R[i][j] += Q[k][i] * A[k][j];
            }
        }
    }
}

// Функция для получения собственных значений матрицы
vector<double> eigenvaluesFromQR(const vector<vector<double>>& A, double eps) {
    int n = A.size();
    vector<vector<double>> Q, R;
    qrDecomposition(A, Q, R);

    vector<vector<double>> Ak = A;
    while (true) {
        qrDecomposition(Ak, Q, R);
        Ak = matrixMultiply(R, Q);

        bool converged = true;
        for (int i = 0; i < n; ++i) {
            if (abs(Ak[i][i] - R[i][i]) > eps) {
                converged = false;
                break;
            }
        }
        if (converged) break;
    }

    vector<double> eigenvalues;
    for (int i = 0; i < n; ++i) {
        eigenvalues.push_back(Ak[i][i]);
    }

    return eigenvalues;
}

int main() {
    vector<vector<double>> A = { {-6, -3, 7}, {9, 1, -6}, {3, -5, 5} };
    double eps = 1e-6;

    vector<double> eigenvalues = eigenvaluesFromQR(A, eps);

    cout << "Собственные значения матрицы:" << endl;
    for (int i = 0; i < eigenvalues.size(); ++i) {
        cout << "λ" << i + 1 << " = " << eigenvalues[i] << endl;
    }

    return 0;
}
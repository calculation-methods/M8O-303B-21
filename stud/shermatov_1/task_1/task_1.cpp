#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>


using namespace std;

typedef vector<vector<double>> Matrix;
typedef vector<double> Vector;

void printMatrix(const Matrix &mat) {
    for (const auto &row : mat) {
        for (double val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void printVector(const Vector &vec) {
    for (double val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

double determinant(const Matrix& mat) {
    int n = mat.size();
    
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return mat[0][0];
    }

    double det = 0;
    Matrix submatrix(n - 1, vector<double>(n - 1));

    for (int i = 0; i < n; i++) {
        int subi = 0;
        for (int j = 1; j < n; j++) {
            int subj = 0;
            for (int k = 0; k < n; k++) {
                if (k == i) {
                    continue;
                }
                submatrix[subi][subj] = mat[j][k];
                subj++;
            }
            subi++;
        }
        det += (i % 2 == 1 ? -1 : 1) * mat[0][i] * determinant(submatrix);
    }

    return det;
}

pair<Matrix, Matrix> luDecomposition(const Matrix &A) {
    int n = A.size();
    Matrix L(n, vector<double>(n, 0.0));
    Matrix U(n, vector<double>(n, 0.0));

    for (int i = 0; i < n; i++) {
        L[i][i] = 1.0;

        for (int k = i; k < n; k++) {
            double sum = 0;
            for (int j = 0; j < i; j++) {
                sum += L[i][j] * U[j][k];
            }
            U[i][k] = A[i][k] - sum;
        }

        for (int k = i; k < n; k++) {
            double sum = 0;
            for (int j = 0; j < i; j++) {
                sum += L[k][j] * U[j][i];
            }
            L[k][i] = (A[k][i] - sum) / U[i][i];
        }
    }

    return make_pair(L, U);
}

Vector solveLinearEquationSystem(const Matrix &A, const Vector &b) {
    int n = A.size();
    Vector x(n);
    Matrix L, U;
    tie(L, U) = luDecomposition(A);

    // Solve Ly = b
    Vector y(n);
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }

    // Solve Ux = y
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }

    return x;
}

Matrix inverseMatrix(const Matrix &A) {
    int n = A.size();
    Matrix inverse(n, Vector(n, 0.0));
    Matrix L, U;
    tie(L, U) = luDecomposition(A);

    Matrix identity(n, Vector(n, 0.0));
    for (int i = 0; i < n; i++) {
        identity[i][i] = 1.0;
        Vector b = identity[i];
        Vector x = solveLinearEquationSystem(A, b);
        for (int j = 0; j < n; j++) {
            inverse[j][i] = x[j];
        }
    }

    return inverse;
}

int main() {
    Matrix A = {{1, 4, -9, 7},
                 {2, -2, -2, 3},
                 {-1, 3, -9, -1},
                 {-5, 2, 2, 1}};
    Vector b = {-67, -57, -26, 52};

    Vector x = solveLinearEquationSystem(A, b);

    cout << "Solution x:" << endl;
    printVector(x);

    Matrix A_inv = inverseMatrix(A);

    cout << "Inverse matrix A_inv:" << endl;
    printMatrix(A_inv);
    
    double det = determinant(A);
    cout << "Determinant:" << det << endl;

    return 0;
}
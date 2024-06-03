#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int N = 4; // размерность системы

vector<vector<double>> A = { {10, 0, 2, 4}, {2, 16, -3, 8}, {1, 5, 11, -4}, {8, 1, 6, -17} };
vector<double> b = { 110, 128, 102, 81 };

vector<double> solveJacobi(vector<vector<double>> A, vector<double> b, double eps) {
    vector<double> x(N, 0.0); // начальное приближение
    vector<double> x_new(N);
    int iter = 0;

    while (true) {
        for (int i = 0; i < N; i++) {
            double sum = 0;
            for (int j = 0; j < N; j++) {
                if (j != i) {
                    sum += A[i][j] * x[j];
                }
            }
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        double error = 0;
        for (int i = 0; i < N; i++) {
            error += abs(x_new[i] - x[i]);
        }

        if (error < eps) {
            break;
        }

        x = x_new;
        iter++;
    }

    cout << "The Jacobie method converges after " << iter << " iterations." << endl;
    return x_new;
}

vector<double> solveGaussSeidel(vector<vector<double>> A, vector<double> b, double eps) {
    vector<double> x(N, 0.0); // начальное приближение
    vector<double> x_new(N);
    int iter = 0;

    while (true) {
        for (int i = 0; i < N; i++) {
            double sum1 = 0;
            for (int j = 0; j < i; j++) {
                sum1 += A[i][j] * x_new[j];
            }

            double sum2 = 0;
            for (int j = i + 1; j < N; j++) {
                sum2 += A[i][j] * x[j];
            }

            x_new[i] = (b[i] - sum1 - sum2) / A[i][i];
        }

        double error = 0;
        for (int i = 0; i < N; i++) {
            error += abs(x_new[i] - x[i]);
        }

        if (error < eps) {
            break;
        }

        x = x_new;
        iter++;
    }

    cout << "The Seidel method converges after " << iter << " iterations." << endl;
    return x_new;
}

int main() {
    double eps = 1e-6;

    vector<double> solutionJacobi = solveJacobi(A, b, eps);
    vector<double> solutionSeidel = solveGaussSeidel(A, b, eps);

    cout << "Solution by Jacobie:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "x[" << i + 1 << "] = " << solutionJacobi[i] << endl;
    }

    cout << "\nSolution by Seidel:" << endl;
    for (int i = 0; i < N; i++) {
        cout << "x[" << i + 1 << "] = " << solutionSeidel[i] << endl;
    }

    return 0;
}
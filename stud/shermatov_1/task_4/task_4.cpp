#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double EPSILON = 1e-6; // точность вычислений

vector<vector<double>> A = {{3, 2, 6}, {2, -3, -7}, {6, 7, 3}}; // исходная матрица

void printMatrix(const vector<vector<double>>& M) {
    for (const auto& row : M) {
        for (double elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

pair<vector<double>, vector<vector<double>>> jacobiEigenvalue(const vector<vector<double>>& A) {
    int n = A.size();
    vector<vector<double>> R(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        R[i][i] = 1.0;
    }

    bool changed = true;
    while (changed) {
        changed = false;
        for (int p = 0; p < n; p++) {
            for (int q = p + 1; q < n; q++) {
                if (abs(A[p][q]) > EPSILON) {
                    changed = true;
                    double phi = (A[q][q] - A[p][p]) / (2.0 * A[p][q]);
                    double t = (phi >= 0) ? 1.0 / (phi + sqrt(1 + phi * phi)) : -1.0 / (-phi + sqrt(1 + phi * phi));
                    double c = 1.0 / sqrt(1 + t * t);
                    double s = t * c;

                    vector<double> Rp = R[p];
                    vector<double> Rq = R[q];
                    for (int i = 0; i < n; i++) {
                        R[p][i] = c * Rp[i] - s * Rq[i];
                        R[q][i] = s * Rp[i] + c * Rq[i];
                    }

                    for (int i = 0; i < n; i++) {
                        if (i != p && i != q) {
                            double Api = A[i][p];
                            double Aiq = A[q][i];
                            A[i][p] = c * Api - s * Aiq;
                            A[p][i] = A[i][p];
                            A[i][q] = c * Aiq + s * A[i][q];
                            A[q][i] = A[i][q];
                        }
                    }

                    double App = A[p][p];
                    double Aqq = A[q][q];
                    double Apq = A[p][q];
                    A[p][p] = c * c * App - 2.0 * c * s * Apq + s * s * Aqq;
                    A[q][q] = s * s * App + 2.0 * c * s * Apq + c * c * Aqq;
                    A[p][q] = 0.0;
                    A[q][p] = 0.0;
                }
            }
        }
    }

    vector<double> eigenvalues;
    vector<vector<double>> eigenvectors;
    for (int i = 0; i < n; i++) {
        eigenvalues.push_back(A[i][i]);
        vector<double> eigenvector;
        for (int j = 0; j < n; j++) {
            eigenvector.push_back(R[j][i]);
        }
        eigenvectors.push_back(eigenvector);
    }

    return {eigenvalues, eigenvectors};
}

int main() {
    pair<vector<double>, vector<vector<double>>> result = jacobiEigenvalue(A);
    
    cout << "Собственные значения:" << endl;
    for (double val : result.first) {
        cout << val << endl;
    }
    
    cout << "Собственные векторы:" << endl;
    for (const auto& vec : result.second) {
        for (double elem : vec) {
            cout << elem << " ";
        }
        cout << endl;
    }

    return 0;
}
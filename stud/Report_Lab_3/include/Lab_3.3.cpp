#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

double eval(const vector<double>& a, double x) {
    double result = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        result += a[i] * pow(x, i);
    }
    return result;
}

double mistakes_sum(vector<double> x, vector<double> y, vector<double> y_approx) {
    double sum = 0.0;
    for (size_t i = 0; i < x.size(); ++i) {
        double error = y[i] - y_approx[i];
        sum += pow(error,2);
    }
    return sum;
}

vector<double> coeffs(vector<double> x, vector<double> y, int d) {
    int n = x.size();
    vector<double> sumX(2 * d + 1, 0.0);
    vector<double> sumY(d + 1, 0.0);
    vector<double> a(d + 1, 0.0);
    for (int i = 0; i < n; ++i) {
        double xi = x[i];
        double yi = y[i];
        for (int j = 0; j <= 2 * d; ++j) {
            sumX[j] += pow(xi, j);
        }
        for (int j = 0; j <= d; ++j) {
            sumY[j] += yi * pow(xi, j);
        }
    }
    vector<vector<double>> A(d + 1, vector<double>(d + 2, 0.0));
    for (int i = 0; i <= d; ++i) {
        for (int j = 0; j <= d; ++j) {
            A[i][j] = sumX[i + j];
        }
        A[i][d + 1] = sumY[i];
    }
    for (int i = 0; i < d; ++i) {
        for (int k = i + 1; k <= d; ++k) {
            double ratio = A[k][i] / A[i][i];
            for (int j = 0; j <= d + 1; ++j) {
                A[k][j] -= ratio * A[i][j];
            }
        }
    }
    for (int i = d; i >= 0; --i) {
        a[i] = A[i][d + 1];
        for (int j = i + 1; j <= d; ++j) {
            if (j != d + 1) {
                a[i] -= A[i][j] * a[j];
            }
        }
        a[i] /= A[i][i];
    }
    return a;
}

int main() {
    vector<double> x = {-1.0, 0.0, 1.0, 2.0, 3.0, 4.0};
    vector<double> y = {-0.4597, 1.0, 1.5403, 1.5839, 2.010, 3.3464};
    int n = x.size();
    vector<double> coeffs_1 = coeffs(x, y, 1);
    cout << "y = (" << coeffs_1[1] << ")*(x) + " << "(" <<  coeffs_1[0] << ")" << endl;
    vector<double> y_A(n);
    for (int i = 0; i < n; ++i) {
        y_A[i] = eval(coeffs_1, x[i]);
    }
    double mistakes_A = mistakes_sum(x, y, y_A);
    cout << "Mistakes: " << mistakes_A << endl << endl;
    vector<double> coeffs_2 = coeffs(x, y, 2);
    cout << "y = (" << coeffs_2[2] << ")*(x^2) + (" <<  coeffs_2[1] << ")*(x) + " << "(" <<  coeffs_2[0] << ")" << endl;
    vector<double> y_B(n);
    for (int i = 0; i < n; ++i) {
        y_B[i] = eval(coeffs_2, x[i]);
    }
    double mistakes_B = mistakes_sum(x, y, y_B);
    cout << "Mistakes: " << mistakes_B << endl;

    return 0;
}
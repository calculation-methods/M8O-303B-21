#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

#define M_PI 3.14159265358979323846

double precision(double a, double b){
    return abs(a-b);
}

double y_function(double x){
    return cos(x)+x;
}

void lagrange(vector<double> x, vector<double> y, double X, double y_needed) {
    double result = 0;
    for (int i = 0; i < x.size(); ++i) {
        double term = y[i];
        for (int j = 0; j < x.size(); ++j) {
            if (j != i) {
                term = term * (X - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    cout << "Lagrange: " << result << endl;
    double precision_lagrange1 = precision(result, y_needed);
    cout << "Precision: " << precision_lagrange1 << endl;
    return;
}

void newton(vector<double> X, vector<double> Y, double x, double y_needed) {
    int n = X.size();
    double result = 0;
    vector<vector<double>> f(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i) {
        f[i][0] = Y[i];
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < n - i; ++j) {
            f[j][i] = (f[j + 1][i - 1] - f[j][i - 1]) / (X[i + j] - X[j]);
        }
    }
    for (int i = 0; i < n; ++i) {
        double term = f[0][i];
        for (int j = 0; j < i; ++j) {
            term *= (x - X[j]);
        }
        result += term;
    }
    cout << "Newton: " << result << endl;
    double precision_newton1 = precision(result, y_needed);
    cout << "Precision: " << precision_newton1 << endl;
    return;
}

int main() {
    vector<double> x1 = {0, M_PI/6, 2*M_PI/6, 3*M_PI/6};
    vector<double> y1;
   
    double a;
    for (int i = 0; i <= sizeof(x1); i++)
    {
        a = y_function(x1[i]);
        y1.push_back(a);
    }

    vector<double> x2 = {0, M_PI/6, M_PI/4, M_PI/2};
    vector<double> y2;

    for (int i = 0; i <= sizeof(x2); i++)
    {
        a = y_function(x2[i]);
        y2.push_back(a);
    }
    
    double x_needed = 1;
    double y_needed = y_function(x_needed);
    cout << "Y value: " << y_needed << endl << endl;
    lagrange(x1, y1, x_needed, y_needed);
    newton(x1, y1, x_needed,  y_needed);
    cout << endl;
    lagrange(x2, y2, x_needed,  y_needed);
    newton(x2, y2, x_needed,  y_needed);
}

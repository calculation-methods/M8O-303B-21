#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct Spline {
    double a, b, c, d, x;
};

void cubic_spline(vector<double> x, vector<double> f, vector<Spline> splines, double x_needed) {
    int n = x.size();
    vector<double> h(n - 1);
    vector<double> alpha(n - 1);
    vector<double> l(n);
    vector<double> mu(n - 1);
    vector<double> z(n);
    for (int i = 0; i < n - 1; ++i) {
        h[i] = x[i + 1] - x[i];
    }
    for (int i = 1; i < n - 1; ++i) {
        alpha[i] = 3 * (f[i + 1] - f[i]) / h[i] - 3 * (f[i] - f[i - 1]) / h[i - 1];
    }
    l[0] = 1;
    mu[0] = 0;
    z[0] = 0;
    for (int i = 1; i < n - 1; ++i) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }
    l[n - 1] = 1;
    z[n - 1] = 0;
    splines[n - 1].c = 0;

    for (int j = n - 2; j >= 0; --j) {
        splines[j].c = z[j] - mu[j] * splines[j + 1].c;
        splines[j].b = (f[j + 1] - f[j]) / h[j] - h[j] * (splines[j + 1].c + 2 * splines[j].c) / 3;
        splines[j].d = (splines[j + 1].c - splines[j].c) / (3 * h[j]);
        splines[j].a = f[j];
    }

    int j = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (x[i] <= x_needed && x_needed <= x[i + 1]) {
            j = i;
            break;
        }
    }
    double A = f[j];
    double B = splines[j].b;
    double C = splines[j].c;
    double D = splines[j].d;
    double y_needed = A + B * (x_needed - x[j]) + C * pow((x_needed - x[j]), 2) + D * pow((x_needed - x[j]), 3);
    cout << "y_needed = " << y_needed << endl;
}

int main() {
    vector<double> x = {0.0, 1.0, 2.0, 3.0, 4.0};
    vector<double> f = {1.0, 1.5403, 1.5839, 2.01, 3.3464};
    double x_needed = 1.5;
    int n = x.size(); 
    vector<Spline> splines(n);
    for (int i = 0; i < n; ++i) {
        splines[i].x = x[i];
    }
    cubic_spline(x, f, splines, x_needed);
    return 0;
}
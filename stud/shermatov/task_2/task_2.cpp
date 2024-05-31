#include <iostream>
#include <cmath>

using namespace std;

const double a = 4;
const double EPS = 1e-6;
const int MAX_ITER = 1000;

// Функции, задающие систему уравнений
double f1(double x1, double x2) {
    return exp(x1 * x2) + x1 - a;
}

double f2(double x1, double x2) {
    return x1 * x1 - a * x2 - 1;
}

// Частные производные функций
double df1_dx1(double x1, double x2) {
    return x2 * exp(x1 * x2) + 1;
}

double df1_dx2(double x1, double x2) {
    return x1 * exp(x1 * x2);
}

double df2_dx1(double x1, double x2) {
    return 2 * x1;
}

double df2_dx2(double x1, double x2) {
    return -a;
}

// Метод простой итерации
void simpleIterationMethod() {
    double x1 = 0.5; // начальное приближение
    double x2 = 2.0; // начальное приближение
    double prev_x1, prev_x2;

    for (int iter = 0; iter < MAX_ITER; ++iter) {
        prev_x1 = x1;
        prev_x2 = x2;

        x1 = a - exp(x1 * prev_x2);
        x2 = (x1 * x1 - 1) / a;

        if (fabs(x1 - prev_x1) < EPS && fabs(x2 - prev_x2) < EPS) {
            cout << "simple iteration method: x1 = " << x1 << ", x2 = " << x2 << endl;
            cout << "iterations: " << iter << endl;
            break;
        }
    }
}

// Метод Ньютона
void newtonMethod() {
    double x1 = 0.5; // начальное приближение
    double x2 = 2.0; // начальное приближение
    double prev_x1, prev_x2;

    for (int iter = 0; iter < MAX_ITER; ++iter) {
        prev_x1 = x1;
        prev_x2 = x2;

        double det = df1_dx1(x1, x2) * df2_dx2(x1, x2) - df1_dx2(x1, x2) * df2_dx1(x1, x2);
        x1 = prev_x1 - (f1(prev_x1, prev_x2) * df2_dx2(prev_x1, prev_x2) - f2(prev_x1, prev_x2) * df1_dx2(prev_x1, prev_x2)) / det;
        x2 = prev_x2 - (-f1(prev_x1, prev_x2) * df2_dx1(prev_x1, prev_x2) + f2(prev_x1, prev_x2) * df1_dx1(prev_x1, prev_x2)) / det;

        if (fabs(x1 - prev_x1) < EPS && fabs(x2 - prev_x2) < EPS) {
            cout << "Newton's method: x1 = " << x1 << ", x2 = " << x2 << endl;
            cout << "iterations: " << iter << endl;
            break;
        }
    }
}

int main() {
    simpleIterationMethod();
    newtonMethod();

    return 0;
}
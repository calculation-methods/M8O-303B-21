#include <iostream>
#include <cmath>

using namespace std;

// Функция, вычисляющая значение y=x^3 - 4 + x^2
double func(double x) {
    return pow(x, 3) - 4 + pow(x, 2);
}

// Метод прямоугольников
double rectangularMethod(double a, double b, double h) {
    double sum = 0;
    for (double x = a; x < b; x += h) {
        sum += func(x);
    }
    return sum * h;
}

// Метод трапеций
double trapezoidalMethod(double a, double b, double h) {
    int n = (b - a) / h;
    double sum = (func(a) + func(b)) / 2.0;

    for (int i = 1; i < n; i++) {
        sum += func(a + i * h);
    }

    return sum * h;
}

// Метод Симпсона
double simpsonMethod(double a, double b, double h) {
    int n = (b - a) / h;
    double sum = func(a) + func(b);

    for (int i = 1; i < n; i++) {
        sum += 2 * func(a + i * h) + 4 * func((2 * a + i * h) / 2.0);
    }

    return sum * h / 3.0;
}

int main() {
    double x0 = 1.0;
    double xk = 5.0;
    double h1 = 1.0;
    double h2 = 0.5;

    double integral1_rect = rectangularMethod(x0, xk, h1);
    double integral1_trap = trapezoidalMethod(x0, xk, h1);
    double integral1_simpson = simpsonMethod(x0, xk, h1);

    double integral2_rect = rectangularMethod(x0, xk, h2);
    double integral2_trap = trapezoidalMethod(x0, xk, h2);
    double integral2_simpson = simpsonMethod(x0, xk, h2);

    double runge_romberg_rect = (integral2_rect - integral1_rect) / (pow(2, 2) - 1);
    double runge_romberg_trap = (integral2_trap - integral1_trap) / (pow(2, 2) - 1);
    double runge_romberg_simpson = (integral2_simpson - integral1_simpson) / (pow(2, 4) - 1);

    cout << "Integral with h=" << h1 << " using Rectangular method: " << integral1_rect << endl;
    cout << "Integral with h=" << h1 << " using Trapezoidal method: " << integral1_trap << endl;
    cout << "Integral with h=" << h1 << " using Simpson method: " << integral1_simpson << endl;
    
    cout << "Integral with h=" << h2 << " using Rectangular method: " << integral2_rect << endl;
    cout << "Integral with h=" << h2 << " using Trapezoidal method: " << integral2_trap << endl;
    cout << "Integral with h=" << h2 << " using Simpson method: " << integral2_simpson << endl;

    cout << "Runge-Romberg estimation for Rectangular method: " << runge_romberg_rect << endl;
    cout << "Runge-Romberg estimation for Trapezoidal method: " << runge_romberg_trap << endl;
    cout << "Runge-Romberg estimation for Simpson method: " << runge_romberg_simpson << endl;

    return 0;
}
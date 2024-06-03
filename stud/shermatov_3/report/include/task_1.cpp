#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// Заданная функция
double f(double x) {
    return x * cos(x);
}

// Функция для вычисления многочлена Лагранжа
double lagrangeInterpolation(const vector<double>& x, const vector<double>& y, double x_val) {
    double result = 0.0;
    for (int i = 0; i < x.size(); ++i) {
        double term = y[i];
        for (int j = 0; j < x.size(); ++j) {
            if (i != j) {
                term *= (x_val - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}

// Функция для вычисления многочлена Ньютона
double newtonInterpolation(const vector<double>& x, const vector<double>& y, double x_val) {
    double result = y[0];
    vector<double> coeffs(y.begin(), y.end());
    for (int i = 1; i < x.size(); ++i) {
        for (int j = x.size() - 1; j > i - 1; --j) {
            coeffs[j] = (coeffs[j] - coeffs[j - 1]) / (x[j] - x[j - i]);
        }
        double term = coeffs[i];
        for (int j = 0; j < i; ++j) {
            term *= (x_val - x[j]);
        }
        result += term;
    }
    return result;
}

int main() {
    // Входные данные
    vector<double> x = {0, M_PI / 6, 2 * M_PI / 6, 3 * M_PI / 6};
    vector<double> y(x.size());
    for (int i = 0; i < x.size(); ++i) {
        y[i] = f(x[i]);
    }
    double x_star = M_PI / 4;

    // Вычисление значений интерполяционных многочленов в точке x*
    double lagrange_result = lagrangeInterpolation(x, y, x_star);
    double newton_result = newtonInterpolation(x, y, x_star);

    // Вывод результатов
    cout << "Значение интерполяционного многочлена Лагранжа в точке x*: " << lagrange_result << endl;
    cout << "Значение интерполяционного многочлена Ньютона в точке x*: " << newton_result << endl;

    // Вычисление погрешности интерполяции в точке x*
    double actual_value = f(x_star);
    double lagrange_error = abs(lagrange_result - actual_value);
    double newton_error = abs(newton_result - actual_value);

    cout << "Погрешность интерполяции для многочлена Лагранжа: " << lagrange_error << endl;
    cout << "Погрешность интерполяции для многочлена Ньютона: " << newton_error << endl;

    return 0;
}
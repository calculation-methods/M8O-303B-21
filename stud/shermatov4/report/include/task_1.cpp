#include <iostream>
#include <cmath>

using namespace std;

// Определение функции и ее производных
double f(double x, double y, double yp) {
    return (5*x + pow(x, 2) + pow(x, 2) * log(fabs(x)));
}

double fy(double x, double y, double yp) {
    return 0;
}

double fyp(double x, double y, double yp) {
    return (-3*y/x - 4*y + 5*x)/x*x;
}

// Метод Эйлера
void euler(double x0, double y0, double yp0, double h, int n) {
    double x = x0, y = y0, yp = yp0;

    for (int i = 0; i < n; i++) {
        double k1 = h * f(x, y, yp);
        double m1 = h * fy(x, y, yp);
        double l1 = h * fyp(x, y, yp);

        y += k1;
        yp += l1;
        x += h;
    }

    cout << "Euler Method: y(" << x << ") = " << y << endl;
}

// Метод Рунге-Кутты
void rungeKutta(double x0, double y0, double yp0, double h, int n) {
    double x = x0, y = y0, yp = yp0;

    for (int i = 0; i < n; i++) {
        double k1 = h * f(x, y, yp);
        double m1 = h * fy(x, y, yp);
        double l1 = h * fyp(x, y, yp);

        double k2 = h * f(x + h/2, y + k1/2, yp + l1/2);
        double m2 = h * fy(x + h/2, y + k1/2, yp + l1/2);
        double l2 = h * fyp(x + h/2, y + k1/2, yp + l1/2);

        y += k2;
        yp += l2;
        x += h;
    }

    cout << "Runge-Kutta Method: y(" << x << ") = " << y << endl;
}

// Метод Адамса 4-го порядка
void adams(double x0, double y0, double yp0, double h, int n) {
    double x = x0, y = y0, yp = yp0;
    double y_prev = y, yp_prev = yp;

    // Выполним первые 3 шага метода Рунге-Кутты для заполнения таблицы
    rungeKutta(x0, y0, yp0, h, 3);

    for (int i = 3; i < n; i++) {
        double y_next = y + h / 24 * (55 * f(x, y, yp) - 59*f(x - h, y_prev, yp_prev) + 37*f(x - 2*h, y_prev, yp_prev) - 9*f(x - 3*h, y_prev, yp_prev));
        double yp_next = yp + h / 24 * (55 * fy(x, y, yp) - 59*fy(x - h, y_prev, yp_prev) + 37*fy(x - 2*h, y_prev, yp_prev) - 9*fy(x - 3*h, y_prev, yp_prev));

        y_prev = y;
        yp_prev = yp;
        y = y_next;
        yp = yp_next;
        x += h;
    }

    cout << "Adams Method: y(" << x << ") = " << y << endl;
}

int main() {
    double x0 = 1.0, y0 = 6.0, yp0 = 8.0;
    double h = 0.1;
    int n = (2 - 1) / h;

    euler(x0, y0, yp0, h, n);
    rungeKutta(x0, y0, yp0, h, n);
    adams(x0, y0, yp0, h, n);

    // Точное решение y = 5*x + x^2 + x^2 * ln|x|
    double exact_solution = 5*x0 + pow(x0, 2) + pow(x0, 2) * log(fabs(x0));
    cout << "Exact solution y(" << x0 << ") = " << exact_solution << endl;

    return 0;
}
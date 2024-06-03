#include <iostream>
#include <cmath>

using namespace std;

// Определение функции и ее производных
double f(double x, double y, double yp) {
    return (2*y - (2*x + 1)*yp) / x;
}

double fy(double x, double y, double yp) {
    return 0;
}

double fyp(double x, double y, double yp) {
    return -y / x;
}

// Метод стрельбы (метод множителей Лагранжа)
double shoot(double x0, double y0, double yp0, double x_target, double h) {
    double x = x0, y = y0, yp = yp0;
    
    while (x < x_target) {
        y += h * yp;
        yp += h * f(x, y, yp);
        x += h;
    }
    
    return y;
}

int main() {
    double x0 = 0.0;
    double y0 = 2.0;
    double yp0 = 0.0;
    double h = 0.01;
    double x_target = 1.0;
    
    // Вычисляем значение y(1) с помощью метода стрельбы
    double y_target = shoot(x0, y0, yp0, x_target, h);
    cout << "Solution using shooting method: y(1) = " << y_target << endl;
    
    // Вычисляем значение y(1) с точным решением
    double y_exact = exp(2.0);
    cout << "Exact solution: y(1) = " << y_exact << endl;
    
    // Рассчитываем погрешность с использованием метода Рунге-Ромберга
    double error = abs(y_exact - y_target);
    cout << "Error: " << error << endl;
    
    return 0;
}
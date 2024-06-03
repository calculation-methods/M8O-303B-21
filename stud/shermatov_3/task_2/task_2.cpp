#include <iostream>
#include <Eigen/Dense>
#include <vector>

using namespace std;
using namespace Eigen;

// Функция для построения кубического сплайна
void cubicSpline(const vector<double>& x, const vector<double>& y,
                 double x0, double y0, double x4, double y4) {
    int n = x.size() - 1;
    VectorXd h = VectorXd::Map(&x[1], n) - VectorXd::Map(&x[0], n);
    VectorXd b = VectorXd::Map(&y[1], n) - VectorXd::Map(&y[0], n);

    MatrixXd A(n - 1, n - 1);
    A.setZero();
    A.diagonal() = (h.segment(0, n - 2) + h.segment(1, n - 2)) * 2.0;
    A.diagonal(1) = h.segment(1, n - 2);
    A.diagonal(-1) = h.segment(1, n - 2);
    
    VectorXd c = A.fullPivLu().solve(b);

    VectorXd a(n + 1), d(n + 1);
    a.head(n) = y.head(n);
    d.head(n) = c;
    d.tail(1) = (c.tail(1) - c(n - 2)) / h(n - 2);
    a.tail(1) = y.tail(1);

    // Вывод коэффициентов сплайнов
    cout << "Коэффициенты сплайнов:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "S" << i << "(x) = " << d(i) << "(x - " << x[i] << ")^3 + " << c(i) << "(x - " << x[i] << ")^2 + " << b(i) << "(x - " << x[i] << ") + " << a(i) << endl;
    }

    // Нахождение значения функции в точке x*
    double x_star = 0.8;
    int idx = distance(x.begin(), lower_bound(x.begin(), x.end(), x_star)) - 1;
    double dx = x_star - x[idx];
    double result = a(idx) + b(idx) * dx + c(idx) * dx * dx + d(idx) * dx * dx * dx;

    cout << "Значение функции в точке x*: " << result << endl;
}

int main() {
    vector<double> x = {0, 0.45345, 0.52360, 2.7183, 14.778};
    vector<double> y = {0, 1, 2, 1, 2};

    double x0 = x[0], y0 = 0;
    double x4 = x.back(), y4 = 0;

    cubicSpline(x, y, x0, y0, x4, y4);

    return 0;
}
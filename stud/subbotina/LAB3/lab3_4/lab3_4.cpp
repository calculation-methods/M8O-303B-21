#include <iostream>
#include <locale.h>
#include "table_function.h"

using namespace std;

int main() {
    setlocale(0, "");
    int n;
    cout << "Введите число точек: ";
    cin >> n;
    std::vector<double> x(n), y(n);
    cout << "Введите Xi: \n";
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    cout << "Введите Yi: \n";
    for (int i = 0; i < n; ++i) {
        cin >> y[i];
    }
    double x0;
    cout << "Введите X*: \n";
    cin >> x0;

    cout.precision(4);
    cout << fixed;
    table_function f(x, y);
    cout << "Первая производная функции в точке x0 = " << x0 << ", f'(x0) = " << f.derivative1(x0) << endl;
    cout << "Вторая производная функции в точке x0 = " << x0 << ", f''(x0) = " << f.derivative2(x0) << endl;
}

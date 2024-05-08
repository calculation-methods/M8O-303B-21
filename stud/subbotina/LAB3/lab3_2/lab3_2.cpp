#include <iostream>
#include <locale.h>
#include "spline.h"

using namespace std;

int main() {
    setlocale(0, "");
    int n;
    cout << "Введите число точек: ";
    cin >> n;
    cout << "Введите Xi: \n";
    vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    cout << "Введите Yi: \n";
    for (int i = 0; i < n; ++i) {
        cin >> y[i];
    }
    cout << "Введите точку X* для подсчета значения функции: ";
    double point;
    cin >> point;

    cout.precision(5);
    cout << fixed;
    Spline spline(x, y);
    cout << "Сплайн: \n" << spline << '\n';
    cout << "Значение в точке X*: " << spline(point) << "\n";
}

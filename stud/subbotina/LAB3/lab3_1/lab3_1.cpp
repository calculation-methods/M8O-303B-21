#include <cmath>
#include <locale.h>
#include "interpolation.h"

using namespace std;

int main() {
    setlocale(0, "");
    cout << "Введите число точек Xi: ";
    int n;
    cin >> n;
    cout << "Введите Xi: \n";
    vector<double> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        y[i] = atan(1 / x[i]) + x[i];

    }
    double point;
    cout << "Введите точку X* для подсчета погрешности итерполяции: ";
    cin >> point;
    Lagrange l(x, y);
    Polynom lagrange = l();
    cout << "Интерполяционный многочлен Лагранжа: \n" << lagrange << '\n';
    cout << "Погрешность в точке Х*: " << abs(lagrange(point) - asin(point) - point) << '\n';

    Newton ne(x, y);
    Polynom newton = ne();
    cout << "Интерполяционный многочлен Ньютона: \n" << newton << '\n';
    cout << "Погрешность в точке Х*: " << abs(newton(point) - asin(point) - point) << '\n';
}

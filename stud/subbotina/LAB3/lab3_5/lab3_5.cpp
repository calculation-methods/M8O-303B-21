#include <iostream>
#include <locale.h>
#include "integrate.h"

using namespace std;

double f(double x) {
    return (x * sqrt(2 * x + 3));
}

int main() {
    setlocale(0, "");
    cout << "Введите X0 и Xk: \n";
    double l, r;
    cin >> l >> r;
    cout << "Введите h1 и h2: \n";
    double h1, h2;
    cin >> h1 >> h2;

    double rect1 = int_rect(l, r, h1, f);
    cout << "Метод прямоугольников с шагом " << h1 << ": " << rect1 << endl;
    double trap1 = int_trap(l, r, h1, f);
    cout << "Метод трапеций с шагом " << h1 << ": " << trap1 << endl;
    double simp1 = int_simp(l, r, h1, f);
    cout << "Метод Симпсона с шагом " << h1 << ": " << simp1 << endl;

    cout << endl;

    double rect2 = int_rect(l, r, h2, f);
    cout << "Метод прямоугольников с шагом " << h2 << ": " << rect2 << endl;
    double trap2 = int_trap(l, r, h2, f);
    cout << "Метод трапеций с шагом " << h2 << ": " << trap2 << endl;
    double simp2 = int_simp(l, r, h2, f);
    cout << "Метод Симпсона с шагом " << h2 << ": " << simp2 << endl;

    cout << endl;

    double rect_rr = abs(runge_romberg(rect1, rect2, h2 / h1, 2));
    cout << "Погрешность вычислений методом прямоугольников: " << rect_rr << endl;
    double trap_rr = abs(runge_romberg(trap1, trap2, h2 / h1, 2));
    cout << "Погрешность вычислений методом трапеций: " << trap_rr << endl;
    double simp_rr = abs(runge_romberg(simp1, simp2, h2 / h1, 4));
    cout << "Погрешность вычислений методом Симпсона: " << simp_rr << endl;
}

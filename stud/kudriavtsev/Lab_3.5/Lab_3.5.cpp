#include <iostream>
#include <cmath>

using namespace std;

double y_function(double x)
{
    return pow(x, 2) / (pow(x, 3) - 27);
}

double rect(double X0, double Xk, double h)
{
    double sum = 0;
    while (X0 + h < Xk)
    {
        sum += y_function(X0 + h / 2);
        X0 += h;
    }

    return sum * h;
}

double trap(double X0, double Xk, double h)
{
    double sum = 0;

    while (X0 + h < Xk)
    {
        sum += (y_function(X0 + h) + y_function(X0));
        X0 += h;
    }

    return sum * h * 0.5;
}

double simp(double X0, double Xk, double h)
{
    double sum = 0;
    X0 += h;
    while (X0 + h < Xk)
    {
        sum += y_function(X0 - h) + 4 * y_function(X0 - h / 2) + y_function(X0);
        X0 += h;
    }

    return sum * h / 6;
}

double runge(double h1, double h2, double i1, double i2, double p)
{
    return i1 + (i1 - i2) / (pow((h2 / h1), p) - 1);
}

int main() {
    double X0 = -2;
    double Xk = 2;
    double h1 = 1;
    double h2 = 0.5;

    cout << "Rect1: " << rect(X0, Xk, h1) << endl;
    cout << "Rect2: " << rect(X0, Xk, h2) << endl;
    cout << "Rect mistakes: " << runge(h1, h2, rect(X0, Xk, h1), rect(X0, Xk, h2), 1) << endl << endl;

    cout << "Trap1: " << trap(X0, Xk, h1) << endl;
    cout << "Trap2: " << trap(X0, Xk, h2) << endl;
    cout << "Trap mistakes: " << runge(h1, h2, trap(X0, Xk, h1), trap(X0, Xk, h2), 2) << endl << endl;

    cout << "Simp1: " << simp(X0, Xk, h1) << endl;
    cout << "Simp2: " << simp(X0, Xk, h2) << endl;
    cout << "Simp mistakes: " << runge(h1, h2, simp(X0, Xk, h1), simp(X0, Xk, h2), 4) << endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool leq(double a, double b)
{
    return (a < b) || (abs(b - a) < 1e-9);
}

double derivative(vector<double> X, vector<double> Y, double x_needed)
{
    double result = 0;
    for (int i = 0; i < X.size() - 1; ++i)
    {
        if (X[i] < x_needed && leq(x_needed, X[i + 1]))
        {
            result = (Y[i + 1] - Y[i - 1]) / (X[i + 1] - X[i - 1]);
        }
    }
    return result;
}

double derivative_2(vector<double> X, vector<double> Y, double x_needed)
{
    double result = 0.0;
    for (int i = 0; i < X.size() - 1; ++i)
    {
        if (X[i] < x_needed && leq(x_needed, X[i + 1]))
        {
            result = (Y[i - 1] - 2 * Y[i] + Y[i + 1]) / pow((X[i + 1] - X[i]), 2);
        }
    }
    return result;
}


int main()
{
    vector<double> x = {0.2, 0.5, 0.8, 1.1, 1.4};
    vector<double> y = {12.906, 5.5273, 3.8777, 3.2692, 3.0319};
    double x_needed = 0.8;
    double y_needed1 = derivative(x, y, x_needed);
    double y_needed2 = derivative_2(x, y, x_needed);
    cout << "f'(x_needed) = " << y_needed1 << endl;
    cout << "f\"(x_needed) = " << y_needed2 << endl;
}
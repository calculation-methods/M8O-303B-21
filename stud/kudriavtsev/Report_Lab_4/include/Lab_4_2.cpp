#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double y_solution(double x) {
    return (exp(x) - 1 + 1 / (exp(x) + 1));
}

double y_derivative_2(double x, double y, double yp) {
    return ((exp(x) + 1) * yp - 2 * y - exp(x) * y);
}


double mistake_counter(vector<double> A, vector<double> B, vector<double> C, double d){
    double total_error = 0;
    for (int i = 0; i < C.size(); ++i) {
        double error = abs(A[i] - B[i]) / d;
        if(error > total_error) {
            total_error = error;
        }
    }
    return total_error;
}

void runge_kutt(double h, double x0, double y0, double yp0, double xf, vector<double>& x_vals, vector<double>& y_vals) {
    double k1, k2, k3, k4;
    double y = y0, yp = yp0;
    for (double x = x0; x < xf; x += h) {
        x_vals.push_back(x);
        y_vals.push_back(y);
        k1 = h * yp;
        k2 = h * (yp + 0.5 * k1);
        k3 = h * (yp + 0.5 * k2);
        k4 = h * (yp + k3);
        y = y + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        yp = yp + (y_derivative_2(x, y, yp) + y_derivative_2(x + h, y + k1, yp + k1)) / 2;
    }
}

double shootingMethod(double h, double x0, double y0, double x_end, double y_end, double g) {
    double tolerance = 0.000001;
    double g1 = g;
    double g2 = g + 0.1;

    double f1, f2;

    while (true) {
        vector<double> x_vals, y_vals1, y_vals2;
        runge_kutt(h, x0, y0, g1, x_end, x_vals, y_vals1);
        runge_kutt(h, x0, y0, g2, x_end, x_vals, y_vals2);
        f1 = y_vals1.back() - y_end;
        f2 = y_vals2.back() - y_end;
        if (fabs(f1) < tolerance) {
            return g1;
        }
        if (fabs(f2) < tolerance) {
            return g2;
        }
        double g_new = g1 - f1 * (g2 - g1) / (f2 - f1);
        g1 = g2;
        g2 = g_new;
    }
}

void finite_diff(double h, double x0, double y0, double x_end, double y_end, vector<double>& x_vals, vector<double>& y_vals) {
    int n = (x_end - x0) / h;
    vector<double> a(n + 1), b(n + 1), c(n + 1), d(n + 1), y(n + 1);

    for (int i = 0; i <= n; ++i) {
        x_vals.push_back(x0 + i * h);
    }

    a[0] = 0;
    b[0] = 1;
    c[0] = 0;
    d[0] = y0;

    for (int i = 1; i < n; ++i) {
        double x = x0 + i * h;
        a[i] = 1 / (h * h) - tan(x) / (2 * h);
        b[i] = -2 / (h * h) + 2;
        c[i] = 1 / (h * h) + tan(x) / (2 * h);
        d[i] = 0;
    }

    a[n] = 0;
    b[n] = 1;
    c[n] = 0;
    d[n] = y_end;

    for (int i = 1; i <= n; ++i) {
        double m = a[i] / b[i - 1];
        b[i] -= m * c[i - 1];
        d[i] -= m * d[i - 1];
    }

    y[n] = d[n] / b[n];
    for (int i = n - 1; i >= 0; --i) {
        y[i] = (d[i] - c[i] * y[i + 1]) / b[i];
    }

    for (int i = 0; i <= n; ++i) {
        y_vals.push_back(y[i]);
    }
}

int main() {
    double x0 = 0.0, xf = 1.0;
    double y0 = 0.0, yf = y_solution(1.0);
    double h = 0.1;
    double epsilon = 0.000001;

    vector<double> X, Y;
    for (double x = x0; x <= xf; x += h) {
        X.push_back(x);
        Y.push_back(y_solution(x));
    }
    vector<double> shooting_x, shooting_y;
    double initial_guess = (yf - y0) / (xf - x0);
    double yp0 = shootingMethod(h, x0, y0, xf, yf, initial_guess);
    runge_kutt(h, x0, y0, yp0, xf, shooting_x, shooting_y);
    vector<double> fd_x, fd_y;
    finite_diff(h, x0, y0, xf, yf, fd_x, fd_y);
    cout.precision(4);
    cout.setf(ios::fixed);
    cout << "x:      ";
    for (int i = 0; i < X.size(); ++i) {
        cout <<  X[i] << "  ";
    }
    cout << endl;
    cout << "y:      ";
    for (int i = 0; i < Y.size(); ++i) {
        cout <<  Y[i] << "  ";
    }
    cout << endl;
    cout << "Shoot:  ";
    for (int i = 0; i < shooting_y.size(); ++i) {
        cout <<  shooting_y[i] << "  ";
    }
    cout << endl;
    cout << "FinDif: ";
    for (int i = 0; i < fd_y.size(); ++i) {
        cout <<  fd_y[i] << "  ";
    }
    cout << endl << endl;
    vector<double> shooting_x_half, shooting_y_half;
    runge_kutt(h / 2, x0, y0, yp0, xf, shooting_x_half, shooting_y_half);
    double shooting_error = mistake_counter(shooting_y_half, shooting_y, shooting_x, 15.0);
    vector<double> fd_x_half, fd_y_half;
    finite_diff(h / 2, x0, y0, xf, yf, fd_x_half, fd_y_half);
    double fd_error = mistake_counter(fd_y_half, fd_y, fd_x, 3.0);
    cout << "Runge_Romberg shooting mistake: " << shooting_error << endl;
    cout << "Runge_Romberg finite diff mistake: " << fd_error << endl;
    return 0;
}
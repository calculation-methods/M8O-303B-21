#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

double y_derivative_2(double x, double y, double y_derivative_1) {
    double result = 2.0*(tan(x))*(y_derivative_1) + 3.0*y;
    return result;
}

double y_solution(double x) {
    double cos_x = cos(x);
    double result = pow(cos_x,3.0) + sin(x)*(1.0 + 2.0*pow(cos_x,2.0));
    return result;
}

vector<double> euler(double a, double b, double h) {
    int steps = (b - a) / h + 1;
    vector<double> x(steps);
    vector<double> y(steps);
    vector<double> y_derivative_1(steps);
    x[0] = 0.0;
    y[0] = 1.0;
    y_derivative_1[0] = 3.0;
    for (int i = 1; i < steps; ++i) {
        x[i] = x[i - 1] + h;
        y_derivative_1[i] =  y_derivative_1[i - 1] - h*(y_derivative_2(x[i - 1], y[i - 1],  y_derivative_1[i - 1]));
        y[i] = y[i - 1] + h * y_derivative_1[i - 1];
    }
    return y;
}

vector<vector <double>> runge_kutt(double a, double b, double h) {
    int steps = (b - a) / h + 1;
    vector<double> x(steps);
    vector<double> y(steps);
    vector<double> y_derivative_1(steps);
    vector<double> K(4, 0.0);
    vector<double> L(4, 0.0);
    x[0] = a;
    y[0] = 1.0;
    y_derivative_1[0] = 3.0;
    for (int i = 1; i < steps; ++i) {
        x[i] = x[i - 1] + h;
        for (int j = 1; j < K.size(); ++j) {
            K[0] = h * y_derivative_1[i - 1];
            L[0] = h * y_derivative_2(x[i - 1], y[i - 1], y_derivative_1[i - 1]);
            K[j] = h * (y_derivative_1[i - 1] + L[j - 1]/2);
            L[j] = h * y_derivative_2(x[i - 1] + h/ 2, y[i - 1] + K[j - 1]/2, y_derivative_1[i - 1] + L[j - 1]/2);
        }
        double delta_y = (K[0] + 2 * K[1] + 2 * K[2] + K[3])/6;
        double delta_y_dir = (L[0] + 2 * L[1] + 2 * L[2] + L[3])/6;
        y[i] = y[i - 1] + delta_y;
        y_derivative_1[i] = y_derivative_1[i - 1] - delta_y_dir;
    }
    return {y, y_derivative_1};
}


vector<double> adams(double a, double b, double h) {
    int steps = (b - a) / h + 1;
    vector<double> x;
    vector<double> y(steps, 0);
    vector<double> y_dir(steps, 0);
    for (double i = a; i < b+h; i += h) {
        x.push_back(i);
    }
    vector<double> y_start = runge_kutt(a, a + 3 * h, h)[0];
    vector<double> y_dir_start = runge_kutt(a, a + 3 * h, h)[1];
    for (int i = 0; i < y_start.size(); ++i) {
        y[i] = y_start[i];
        y_dir[i] = y_dir_start[i];
    }
    for (int i = 4; i < steps; ++i) {
        y_dir[i] = (y_dir[i - 1] - h * (55 * y_derivative_2(x[i - 1], y[i - 1], y_dir[i - 1]) - 59 * y_derivative_2(x[i - 2], y[i - 2], y_dir[i - 2])+ 37 * y_derivative_2(x[i - 3], y[i - 3], y_dir[i - 3]) - 9 * y_derivative_2(x[i - 4], y[i - 4], y_dir[i - 4])) / 24);
        y[i] = y[i - 1] + h * y_dir[i - 1];
    }
    return y;
}

double runge_romberg(double A, double B, int p) {
    return (A - B) / (pow(2, p) - 1);
}

int main() {
    double h = 0.1;
    double a = 0;
    double b = 1;
    vector<double> x, y;
    int n = static_cast<int>((b - a) / h) + 1;
    for (double i = a; i < b+h; i += h) {
        x.push_back(i);
        y.push_back(y_solution(i));
    }


    cout << fixed << setprecision(6);
    vector <double> res_euler = euler(a, b, h);
    vector <double> res_runge_kutt = runge_kutt(a, b, h)[0];
    vector <double> res_adams = adams(a, b, h);
    vector <double> res_euler_2 = euler(a, b, h/2);
    vector <double> res_runge_kutt_2 = runge_kutt(a, b, h/2)[0];
    vector <double> res_adams_2 = adams(a, b, h/2);
    cout << "x\t\ty\t\tEuler\t\tRunge_Kutt\tAdams\t\tEuler_mistakes\tRunge_K_mistakes  Adams_mistakes)\n";
        for (int i = 0; i < n; ++i) {
            double y_precise = y_solution(x[i]);
            cout << x[i] << "\t" << y_precise  << "\t"  
                  << res_euler[i]<< "\t" << res_runge_kutt[i]  << "\t" << res_adams[i]  << "\t" 
                  << abs(res_euler[i] - y_precise) << "\t" << abs(res_runge_kutt[i] - y_precise) << "\t" << abs(res_adams[i] - y_precise) << "\n";
    }
    cout << "\nRunge-Romberg\n";
    cout << "\nx\t\tEuler (h=0.1)\tEuler (h=0.05)\tMistake \n";
    for (int i = 0; i < n; ++i) {
        double res_euler_2_2i = res_euler_2[i * 2];
        double error_estimate = runge_romberg(res_euler[i],  res_euler_2_2i, 1);
        cout << x[i] << "\t" << res_euler[i] << "\t" << res_euler_2_2i << "\t" << error_estimate << "\n";
    }
    cout << "\nx\t\tRunge_Kutt (h=0.1)\tRunge_Kutt  (h=0.05)\tMistake\n";
    for (int i = 0; i < n; ++i) {
        double res_runge_kutt_2_2i = res_runge_kutt_2[i * 2];
        double error_estimate = runge_romberg(res_runge_kutt[i], res_runge_kutt_2_2i, 4);
        cout << x[i] << "\t" << res_runge_kutt[i] << "\t\t" << res_runge_kutt_2_2i << "\t\t" << error_estimate << "\n";
    }
    cout << "\nx\t\tAdams (h=0.1)\t\tAdams (h=0.05)\t\tMistake\n";
    for (int i = 0; i < n; ++i) {
        double res_adams_2_2i = res_adams_2[i * 2];
        double error_estimate = runge_romberg(res_adams[i], res_adams_2_2i, 4);
        cout << x[i] << "\t" << res_adams[i] << "\t\t" << res_adams_2_2i << "\t\t" << error_estimate << "\n";
    }
    return 0;
}
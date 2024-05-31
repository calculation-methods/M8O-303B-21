#include <iostream>
#include <cmath>

using namespace std;

double lg(double x) {
    return log10(x);
}

double f(double x) {
    return lg(2*x + 1) - pow(x, 3) + 1;
}

double f_prime(double x) {
    return 2 / (2*x + 1) - 3*x*x;
}

double simpleIteration(double initial_guess, double tolerance, int max_iterations) {
    double x = initial_guess;
    int iter = 0; 
    
    while (iter < max_iterations) {
        double x_new = lg(1 + x*x*x) / 2;
        if (abs(x_new - x) < tolerance) {
            return x_new;
        }
        x = x_new;
        iter++;
    }
    
    cout << "iterations: " << iter << endl;
    
    return x;
}

double newton(double initial_guess, double tolerance, int max_iterations) {
    double x = initial_guess;
    int iter = 0;
    
    while (iter < max_iterations) {
        double dx = f(x) / f_prime(x);
        if (abs(dx) < tolerance) {
            return x + dx;
        }
        x = x - dx;
        iter++;
    }
    
    cout << "iterations: " << iter << endl;
    
    return x;
}

int main() {
    double initial_guess = 2.0; // начальное приближение для положительного корня
    double tolerance = 1e-6;
    int max_iterations = 1000;
    
    cout << "simple iteration method: " << simpleIteration(initial_guess, tolerance, max_iterations) << endl;
    cout << "Newton's method: " << newton(initial_guess, tolerance, max_iterations) << endl;
    
    return 0;
}
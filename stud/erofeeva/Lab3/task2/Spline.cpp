#include <iostream>
#include <vector>
#include <cmath>

using InVector = const std::vector<double> &;


std::vector<double> threeDiagonal(InVector x, InVector y, int n) {
    std::vector<double> p(n-2);
    std::vector<double> q(n-2);
    p[0] = -(x[2]-x[1])/(2*x[3]-2*x[1]);
    q[0] = 3*((y[2]-y[1])/(x[2]-x[1])-(y[1]-y[0])/(x[1]-x[0]))/(2*x[2]-2*x[0]);
    for(int i = 1; i < n - 2; i++){
        p[i] = -(x[i+2]-x[i+1])/((2*x[i+2]-2*x[i])+(x[i+1]-x[i])*p[i-1]);
        q[i] = (3*((y[i+2]-y[i+1])/(x[i+2]-x[i+1])-(y[i+1]-y[i])/(x[i+1]-x[i]))-(x[i+1]-x[i])*q[i-1])/((2*x[i+2]-2*x[i])+(x[i+1]-x[i])*p[i-1]);
    }
    std::vector<double> res(n);
    res[n-1] = q[n-2];
    for(int i = n-2; i > 0; i--){
        res[i] = p[i-1]*res[i+1] + q[i-1];
    }
    return res;
}


std::string sign(double x) {
    return x? " + ": " - ";
}


double spline(InVector x, InVector y, double xu, int n) {
    std::vector<double> a(n-1);
    std::vector<double> b(n-1);
    std::vector<double> c(n-1);
    std::vector<double> d(n-1);
    for(int i = 0; i < n-1; i++) a[i] = y[i];
    c = threeDiagonal(x, y, n);
    for(int i = 0; i < n-2; i++) {
        b[i] = (y[i+1]-y[i])/(x[i+1]-x[i])-(x[i+1]-x[i])*(c[i+1]+2*c[i])/3;
        d[i] = (c[i+1]-c[i])/(x[i+1]-x[i])/3;
    }
    b[n-1] = (y[n]-y[n-1])/(x[n]-x[n-1])-(x[n]-x[n-1])*2*c[n-1]/3;
    d[n-1] = -c[n-1]/(x[n]-x[n-1])/3;

    for(int i = 0; i < n-1; i++){
        std::cout << "x ∈ [" << x[i] << ", " << x[i+1] << "], =>" << std::endl;
        std::cout << "\t s(x) = ";
        std::cout << a[i];
        std::cout << sign(b[i]) << fabs(b[i]) << "(x" << sign(-x[i]) << fabs(x[i]) << ")";
        std::cout << sign(c[i]) << fabs(c[i]) << "(x" << sign(-x[i]) << fabs(x[i]) << ")^2";
        std::cout << sign(d[i]) << fabs(d[i]) << "(x" << sign(-x[i]) << fabs(x[i]) << ")^3";
        std::cout << std::endl << std::endl;
    }

    int j = 0;
    for(int i = 0; i < n-1; i++) {
        if(xu >= x[i] && xu <= x[i+1]) j = i;
    }
    if(!j) return xu;
    xu -= x[j];
    return a[j]+b[j]*xu+c[j]*xu*xu + d[j]*xu*xu*xu;
}


int main(){
    const int n = 5;
    const double xu = -0.5;
    std::vector<double> x = {  -2,      -1,       0,    1,      2       };
    std::vector<double> y = {   0.13534, 0.36788, 1,    2.7183, 7.3891  };
    double Sxu = spline(x, y, xu, n);
    std::cout << "s(x*) = " << Sxu << std::endl;
    return 0;
}
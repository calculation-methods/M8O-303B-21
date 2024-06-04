#include <iostream>
#include <vector>
#include <cmath>


double func(double x){
    return exp(x);
}

double lagrange(const std::vector<double> &x, double xu, int n){
    std::cout << "L(x) = ";
    double res = 0;
    for(int j = 0; j < n; j++) {
        double a = func(x[j]);
        double f = 1;
        for(int i = 0; i < n; i++) {
            if(i != j) a/=x[j] - x[i];
        }
        if(j && a >= 0) {
            std::cout << " + ";
        } else {
            std::cout << " - ";
        }
        std::cout << round(fabs(a)*10000)/10000.0;
        for(int i = 0; i < n; i++) {
            std::cout << "(x";
            if(x[i] >= 0) std::cout << "+";
            std::cout << x[i] << ")";
            if (i != j) f *= xu - x[i];
        }
        res += a*f;
    }
    std::cout << std::endl;
    return res;
}


double Newton(const std::vector<double> &x, double xu, int n){
    std::vector<std::vector<double>> d(n, std::vector<double>(n));
    for(int i = 0; i < n; i++){
        d[i][0] = func(x[i]);
    }
    for(int j = 1 ; j < n; j++){
        for(int i = 0; i < n-j; i++){
            d[i][j] = (d[i][j-1]-d[i+1][j-1])/float(x[i]-x[i+j]);
        }
    }
    std::cout << "N(x) = ";
    double res = 0;
    for(int j = 0; j < n; j++){
        double a = d[0][j];
        double f = 1;
        if(j && a >= 0) {
            std::cout << " + ";
        } else {
            std::cout << " - ";
        }
        std::cout << round(fabs(a)*10000)/10000.0;
        for(int i = 0; i < j; i++) {
            std::cout << "(x";
            if(x[i] >= 0) std::cout << "+";
            std::cout << x[i] << ")";
            f *= xu - x[i];
        }
        res += a*f;
    }
    std::cout << std::endl;
    return res;
}


int main(){
    const int n = 4;
    const double xu = -0.5;
    std::vector<double> Xa = {-2, -1, 0, 1};
    std::vector<double> Xb = {-2, -1, 0.2, 1};

    std::cout << "Многочлен Лагранжа" << std::endl;
    std::cout << "a) ";
    double res = lagrange(Xa, xu, n);
    std::cout << "L(x*)=" << res << std::endl;
    std::cout << "y(x*)=" << func(xu) << std::endl;
    std::cout << "Погрешность: " << fabs(res - func(xu)) << std::endl;

    std::cout << "b) ";
    res = lagrange(Xb, xu, n);
    std::cout << "L(x*)=" << res << std::endl;
    std::cout << "y(x*)=" << func(xu) << std::endl;
    std::cout << "Погрешность: " << fabs(res - func(xu)) << std::endl;
    std::cout << std::endl;


    std::cout << "Многочлен Ньютона" << std::endl;
    std::cout << "a) ";
    res = Newton(Xa, xu, n);
    std::cout << "N(x*)=" << res << std::endl;
    std::cout << "y(x*)=" << func(xu) << std::endl;
    std::cout << "Погрешность: " << fabs(res - func(xu)) << std::endl;

    std::cout << "b) ";
    res = Newton(Xb, xu, n);
    std::cout << "N(x*)=" << res << std::endl;
    std::cout << "y(x*)=" << func(xu) << std::endl;
    std::cout << "Погрешность: " << fabs(res - func(xu)) << std::endl;
    std::cout << std::endl;


    return 0;
}
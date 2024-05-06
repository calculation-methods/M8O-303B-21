#include <iostream>
#include <cmath>

namespace nfunc{
    // f(x) = e^x - 2x - 2
    double f(double x){
        return exp(x) - 2*x - 2;
    }
    // f'(x) = e^x - 2
    double df_dx(double x){
        return exp(x) - 2;
    }
    // f''(x) = e^x
    double ddf_dxdx(double x){
        return exp(x);
    }
    double epsk(double xk, double xk_inc){
        return fabs(xk-xk_inc);
    }
}

namespace sifunc{
    // f(x) = e^x - 2x - 2
    double f(double x){
        return exp(x) - 2*x - 2;
    }
    // x = phi(x), phi(x) = ln(2(x+1))
    double phi(double x){
        return log(2*(x+1));
    }
    // phi'(x) = 1/(x+1)
    double dphi_dx(double x){
        return 1.0/(x+1);
    }
    double epsk(double xk, double xk_inc, double q){
        return q*fabs(xk - xk_inc)/(1-q);
    }
}


double newton(double a, double b, double eps){
    // Проверяем условие сходимости f(x_0)*f''(x_0) > 0
    // Ищем начальное значение
    double x0 = a - eps;
    if(nfunc::f(a)*nfunc::ddf_dxdx(a) > 0){
        x0 = a;
    } else if(nfunc::f(b)*nfunc::ddf_dxdx(b) > 0){
        x0 = b;
    } else {
        return x0;
    }
    // Выполнение итераций самим методом Ньютона
    int k = -1;
    double xk = x0;
    double xk_inc = x0 + 2*eps;
    while (nfunc::epsk(xk, xk_inc) >= eps){
        k += 1;
        xk = xk_inc;
        xk_inc = xk - nfunc::f(xk)/nfunc::df_dx(xk);
    }
    std::cout << "Выполнено " << k << " итераций методом Ньютона" << std::endl;
    return xk_inc;
}


double simple_iterations_method(double x0, double a, double b, double eps){
    // Проверяем условия сходимости
   double q = fabs(sifunc::dphi_dx(x0));
    if ( q <= 0 || q>= 1){
        return a - eps;
    }
    // Выполнение итераций методом простых итераций
    int k = -1;
    double xk = (a + b)/2;
    double xk_inc = x0 + 2*eps;
    while (sifunc::epsk(xk, xk_inc, q) >= eps){
        k += 1;
        xk_inc = xk;
        xk = sifunc::phi(xk_inc);
    }
    return xk_inc;
}


int main(){
    double eps = 0.001;

    double result = newton(1.5, 2, eps);
    std::cout << "\tРезультат применения метода Ньютона:" << std::endl;
    std::cout << round(result*100)/100.0 << std::endl;
    std::cout << "Проверка: f(x) = " << round(nfunc::f(result)*100)/100.0 << std::endl;

    result = simple_iterations_method(2, 1.5, 2, eps);
    std::cout << "\tРезультат применения метода простых итераций:" << std::endl;
    std::cout << round(result*100)/100.0 << std::endl;
    std::cout << "Проверка: f(x) = " << round(sifunc::f(result)*100)/100.0 << std::endl;

    return 0;
}
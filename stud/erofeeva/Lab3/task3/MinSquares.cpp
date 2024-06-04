#include <iostream>
#include <vector>
#include <cmath>


using InVector = std::vector<double> &;
using InMatrix = std::vector<std::vector<double>> &;


double det(InMatrix a){
    double D = 0;
    int size = a.size();
    if(size == 1) return a[0][0];
    double sign = 1;
    for(int k = 0; k < size; k++) {
        std::vector<std::vector<double>> minor(size-1, std::vector<double>(size-1));
        for(int i = 0; i < size-1; i++) {
            for(int j = 0; j < size-1; j++) {
                int mj = (j < k)? j: j+1;
                minor[i][j] = a[i+1][mj];
            }
        }
        double temp = det(minor);
        D += sign*a[0][k]*temp;
        sign *= -1;
    }
    return D;
}

std::vector<double> Cramer(InMatrix a, InVector b, int m){
    std::vector<double> x(m);
    for(int i = 0; i < m; i++) {
        std::vector<std::vector<double>> ai(a);
        for(int j = 0; j < m; j++) {
            ai[j][i] = b[j];
        }
        x[i] = det(ai)/det(a);
    }
    return x;
}


std::string sign(double x) {
    return (x < 0)? " - ": " + ";
}


double minSquare(InVector x, InVector y, int m, int n){
    std::vector<std::vector<double>> a(m, std::vector<double>(m));
    std::vector<double> b(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            for(int k = 0; k < n; k++) {
                a[i][j] += pow(x[k], i+j);
            }
        }
        for(int k = 0; k < n; k++) {
            b[i] += y[k]*pow(x[k], i);
        }
    }
    std::vector<double> z(Cramer(a, b, m));
    double err = 0;
    for(int k = 0; k < n; k++){
        double px = 0;
        for(int i = 0; i < m; i++) {
            px += z[i]*pow(x[k], i);
        }
        err += (px - y[k])*(px - y[k]);
    }
    std::cout << "P(x) = " << z[0];
    for(int i = 1; i < m; i++) {
        std::cout << sign(z[i]) << fabs(z[i]) << "x";
        if(i > 1) std::cout << "^" << i;
    }
    std::cout << std::endl;
    return err;
}


int main(){
    const int n = 6;
    std::vector<double> x = {  -3,      -2,      -1,       0,      1,      2       };
    std::vector<double> y = {   0.04979, 0.13534, 0.36788, 1,      2.7183, 7.3891  };

    std::cout << "МНК, Многочлен 1-ой степени:" << std::endl;
    double res = minSquare(x, y, 2, n);
    std::cout << "Сумма квадратов ошибок: " << res << std::endl;
    std::cout << std::endl;

    std::cout << "МНК, Многочлен 2-ой степени:" << std::endl;
    res = minSquare(x, y, 3, n);
    std::cout << "Сумма квадратов ошибок: " << res << std::endl;
    std::cout << std::endl;
    return 0;
}

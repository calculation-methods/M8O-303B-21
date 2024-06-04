#include <iostream>
#include <vector>
#include <cmath>


using InVector = std::vector<double> &;
using Matrix = std::vector<std::vector<double>>;


Matrix getPolinom(InVector x, InVector y, int n){
    Matrix D(n, std::vector<double>(n));
    for(int i = 0; i < n; i++) {
        D[i][0] = y[i];
    }
    for(int j = 1; j < n; j++) {
        for(int i = 0; i < n-j; i++) {
            D[i][j] = (D[i][j-1] - D[i+1][j-1])/(x[i]-x[i+j]);
        }
    }
    return D;
}


double firstDerivative(InVector x, Matrix &D, double xu, int n) {
    double dydx = 0;
    for(int j = 1; j < n; j++) {
        double f = 0;
        for(int k = 0; k < j; k++) {
            double g = D[0][j];
            for(int i = 0; i < j; i++) {
                if(i!=k) g*=xu-x[i];
            }
            f += g;
        }
        dydx += f;
    }
    return dydx;
}


double secondDerivative(InVector x, Matrix &D, double xu, int n) {
    double ddydxdx = 0;
    for(int j = 2; j < n; j++) {
        double f = 0;
        for(int k = 0; k < j; k++) {
            for(int h = 0; h < j; h++) {
                if (h == k) continue;
                double g = D[0][j];
                for(int i = 0; i < j; i++) {
                    if(i == k || i == h) continue;
                    g *= xu - x[i];
                }
                f += g;
            }
        }
        ddydxdx+= f;
    }
    return ddydxdx;
}


int findInd(InVector x, double xu) {
    double diff = fabs(x[0] - xu);
    for(int i = 1; i < x.size(); i++) {
        if(fabs(x[i] - xu) > diff) return i - 1;
        diff = fabs(x[i] - xu);
    }
    return -1;
}


double nonDiffLeft(InVector x, InVector y, int i) {
    return (y[i+1] - y[i])/(x[i+1] - x[i]);
}


double nonDiffRight(InVector x, InVector y, int i) {
    return (y[i] - y[i-1])/(x[i] - x[i-1]);
}


double nonDiffCentre(InVector x, InVector y, int i) {
    return (y[i+1] - y[i-1])/(x[i+1] - x[i-1]);
}


double nonDiffSecond(InVector x, InVector y, int i){
    return (y[i+1] - 2*y[i] + y[i-1])/((x[i+1] - x[i])*(x[i] - x[i-1]));
}


int main(){
    const int n = 5;
    const double xu = 0.2;
    std::vector<double> x = {  -0.2,     0,     0.2,     0.4,     0.6     };
    std::vector<double> y = {  -0.20136, 0,     0.20136, 0.41152, 0.6435  };

    std::cout << "Производные по безразностным формулам" << std::endl;
    int ind = findInd(x, xu);
    double dydxL = nonDiffLeft(x, y, ind);
    double dydxR = nonDiffRight(x, y, ind);
    double dydxC = nonDiffCentre(x, y, ind);
    double ddydxdxnd = nonDiffSecond(x, y, ind);
    std::cout << "Левая первая производная: " << dydxL << std::endl;
    std::cout << "Правая первая производная: " << dydxR << std::endl;
    std::cout << "Центральная первая производная: " << dydxC << std::endl;
    std::cout << "Вторая производная: " << ddydxdxnd << std::endl;
    std::cout << std::endl;

    std::cout << "Производные от интерполяционных полиномов" << std::endl;
    Matrix D = getPolinom(x, y, n);
    double dydx = firstDerivative(x, D, xu, n);
    double ddydxdx = secondDerivative(x, D, xu, n);
    std::cout << "f' (x*) = " << dydx << std::endl;
    std::cout << "f''(x*) = " << ddydxdx << std::endl;
    std::cout << std::endl;

    return 0;
}
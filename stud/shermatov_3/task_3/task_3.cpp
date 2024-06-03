#include <iostream>
#include <Eigen/Dense>
#include "matplotlibcpp.h"

using namespace std;
using namespace Eigen;
namespace plt = matplotlibcpp;

// Функция для решения задачи приближения многочленами
void approximatePolynomials(const MatrixXd& A, const VectorXd& y, int degree) {
    VectorXd coefficients = (A.transpose() * A).ldlt().solve(A.transpose() * y);

    // Создаем многочлен на основе коэффициентов
    VectorXd x = VectorXd::LinSpaced(100, A.col(1).minCoeff(), A.col(1).maxCoeff());
    MatrixXd polynomial = MatrixXd::Ones(x.rows(), degree + 1);
    for (int i = 1; i <= degree; ++i)
        polynomial.col(i) = x.array().pow(i);

    VectorXd y_approx = polynomial * coefficients;

    // Вычисляем сумму квадратов ошибок
    double error = (y - A * coefficients).squaredNorm();

    // Строим графики
    plt::figure();
    plt::plot(A.col(1), y, "ro");
    plt::plot(x, y_approx, "b-");
    plt::title("График приближаемой функции и приближающего многочлена");
    plt::xlabel("x");
    plt::ylabel("f(x)");
    plt::show();

    cout << "Сумма квадратов ошибок для приближающего многочлена " << degree << "-ой степени: " << error << endl;
}

int main() {
    MatrixXd A(6, 2);
    A << 1, -1.7,
         1, -1.2,
         1, -0.7,
         1, -0.2,
         1, 0.3,
         1, 0.8;

    VectorXd y(6);
    y << 0.52796, 0.43372, 0.24333, 0.03275, 0.12149, 1.4243;

    // Приближение многочленами 1-ой и 2-ой степени
    approximatePolynomials(A, y, 1);
    approximatePolynomials(A, y, 2);

    return 0;
}
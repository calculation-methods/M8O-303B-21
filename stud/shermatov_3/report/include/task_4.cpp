#include <iostream>
#include <vector>

using namespace std;

// Структура для хранения пар (xi, f(xi))
struct DataPoint {
    double x;
    double y;
};

// Функция для нахождения первой производной в точке x*
double firstDerivative(const vector<DataPoint>& data, double x_star) {
    double h = data[1].x - data[0].x; // Шаг изменения x в таблице
    double y_minus = 0.0, y_plus = 0.0;

    // Находим значения f(xi-h) и f(xi+h)
    for (const auto& point : data) {
        if (point.x == x_star - h) {
            y_minus = point.y;
        }
        if (point.x == x_star + h) {
            y_plus = point.y;
        }
    }

    // Вычисляем первую производную
    double derivative = (y_plus - y_minus) / (2 * h);
    
    return derivative;
}

// Функция для нахождения второй производной в точке x*
double secondDerivative(const vector<DataPoint>& data, double x_star) {
    double h = data[1].x - data[0].x; // Шаг изменения x в таблице
    double y_minus = 0.0, y_star = 0.0, y_plus = 0.0;

    // Находим значения f(xi-h), f(xi) и f(xi+h)
    for (const auto& point : data) {
        if (point.x == x_star - h) {
            y_minus = point.y;
        }
        if (point.x == x_star) {
            y_star = point.y;
        }
        if (point.x == x_star + h) {
            y_plus = point.y;
        }
    }

    // Вычисляем вторую производную
    double derivative = (y_plus - 2 * y_star + y_minus) / (h * h);

    return derivative;
}

int main() {
    vector<DataPoint> data = {
        {0.0, 0.0},
        {0.2, 0.048856},
        {0.4, 0.23869},
        {0.6, 0.65596},
        {0.8, 1.4243}
    };

    double x_star = 0.4;
    
    // Находим первую и вторую производные
    double first_deriv = firstDerivative(data, x_star);
    double second_deriv = secondDerivative(data, x_star);

    cout << "Первая производная в точке x* = " << x_star << ": " << first_deriv << endl;
    cout << "Вторая производная в точке x* = " << x_star << ": " << second_deriv << endl;

    return 0;
}
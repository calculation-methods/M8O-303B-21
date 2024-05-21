
#include <iostream>
#include <vector>

using namespace std;


vector<double> zeydel(vector<vector<double>> coef_matrix, vector<double> cons_vector, double exactitude) {
    int N = coef_matrix.size();
    vector<double> roots(N, 0.0);
    vector<double> roots_but_better(N);
    int iterations = 0;
    double error = exactitude + 1.0;

    while (error > exactitude) {
        for (int i = 0; i < N; ++i) {
            double sum1 = 0.0;
            for (int j = 0; j < i; ++j) {
                sum1 += coef_matrix[i][j] * roots_but_better[j];
            }

            double sum2 = 0.0;
            for (int j = i + 1; j < N; ++j) {
                sum2 += coef_matrix[i][j] * roots[j];
            }

            roots_but_better[i] = (cons_vector[i] - sum1 - sum2) / coef_matrix[i][i];
        }
        error = 0.0;
        for (int i = 0; i < N; ++i) {
            error = max(error, abs(roots_but_better[i] - roots[i]));
            roots[i] = roots_but_better[i];
        }
        iterations++;
    }

    cout << "the number of iterations is " << iterations << endl;
    return roots;
}
vector<double> iterations(vector<vector<double>> coef_matrix, vector<double> cons_vector, double exactitude) {
    int N =  coef_matrix.size();
    vector<double> roots(N, 0.0);
    vector<double> roots_but_better(N);
    int iterations = 0;
    double error = exactitude + 1.0;
    while (error > exactitude) {
        for (int i = 0; i < N; ++i) {
            double sum = cons_vector[i];
            for (int j = 0; j < N; ++j) {
                if (j != i) {
                    sum -= coef_matrix[i][j] * roots[j];
                }
            }
            roots_but_better[i] = sum / coef_matrix[i][i];
        }
        error = 0.0;
        for (int i = 0; i < N; ++i) {
            error = max(error, abs(roots_but_better[i] - roots[i]));
            roots[i] = roots_but_better[i];
        }
        iterations++;
    }

    cout << "the number of iterations is " << iterations << endl;
    return roots;
}

int main() {
    vector<vector<double>> coef_matrix = {
        {24, -7, -4, 4},
        {-3, -9, -2, -2},
        {3, 7, 24, 9},
        {1, -6, -2, -15}
    };
    vector<double> cons_vector = {-190, -12, 155, -17};
    double exactitude = 0.001;
    
    cout << "iterations:" << endl;
    vector<double> iteration_result = iterations(coef_matrix, cons_vector, exactitude);
    for (int i = 0; i < coef_matrix.size(); i++){
        cout << iteration_result[i] << " " << endl;
    }
    cout << endl;

    cout << "zeydal:" << endl;
    vector<double> zeydel_result = zeydel(coef_matrix, cons_vector, exactitude);
    for (int i = 0; i < coef_matrix.size(); i++){
        cout << zeydel_result[i] << " " << endl;
    }

    return 0;
}
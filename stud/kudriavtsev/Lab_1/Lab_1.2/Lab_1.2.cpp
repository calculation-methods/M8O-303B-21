#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void print_vector(vector<double> vector_A) {
    int N = vector_A.size();
    cout << "(" << " ";
    for (int i = 0; i < N; i++) {
        cout << vector_A[i] << " ";
    }
    cout << ")" << "";
}

vector<double> run(vector<vector<double>> matrix_A, vector<double> vector_B) {
    int N = vector_B.size();
    vector<double> P(N, 0.0);
    vector<double> Q(N, 0.0);
    P[0] = - matrix_A[0][1] / matrix_A[0][0];
    Q[0] = vector_B[0] / matrix_A[0][0];

    for (int i = 1; i < N - 1; ++i) {
        double C = matrix_A[i][i] + matrix_A[i][i - 1] * P[i - 1];
        P[i] = -matrix_A[i][i + 1] / C;
        Q[i] = (vector_B[i] - matrix_A[i][i - 1] * Q[i - 1]) / C;
    }

    vector<double> answer(N, 0.0);
    double C = matrix_A[N - 1][N - 1] + matrix_A[N - 1][N - 2] * P[N - 2];
    Q[N - 1] = (vector_B[N - 1] - matrix_A[N - 1][N - 2] * Q[N - 2]) / C;
    answer[N - 1] = Q[N - 1];

    for (int i = N - 2; i >= 0; --i) {
        answer[i] = P[i] * answer[i + 1] + Q[i];
    }

    return answer;
}



int main() {
    vector<vector<double>> matrix_A = {
        {14, 9, 0, 0, 0},
        {-8, 14, 6, 0, 0},
        {0, -5, -17, 8, 0},
        {0, 0, 1, 5, -2},
        {0, 0, 0, -4, -10}};

    vector<double> vector_B = {125, -56, 144, 36, 70};
    vector<double> result = run(matrix_A, vector_B);
    cout << "Solution of the system: " << endl;
    print_vector(result);
    return 0;
}
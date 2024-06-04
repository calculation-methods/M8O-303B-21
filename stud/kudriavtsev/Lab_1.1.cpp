#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void print_matrix(const vector<vector<double>> matrix_A) {
    for (const auto& vect : matrix_A) {
        for (auto x : vect) {
            cout << x << " ";
        }
        cout << endl;
    }
}

vector<vector<double>> get_minor(const vector<vector<double>>& matrix_A, int row, int col) {
    vector<vector<double>> minor(matrix_A.size() - 1, vector<double>(matrix_A.size() - 1));

    for (int i = 0, k = 0; i < matrix_A.size(); i++) {
        if (i == row) continue;
        for (int j = 0, l = 0; j < matrix_A.size(); j++) {
            if (j == col) continue;
            minor[k][l] = matrix_A[i][j];
            l++;
        }
        k++;
    }
    return minor;
}

double determinant(const vector<vector<double>>& matrix_A) {
    if(matrix_A.size() == 1) {
        return matrix_A[0][0];
    }
    double det = 0;
    int sign = 1;
    for (int i = 0; i < matrix_A.size(); i++) {
        vector<vector<double>> minor = get_minor(matrix_A, 0, i);
        det += sign * matrix_A[0][i] * determinant(minor);
        sign *= -1;
    }
    return det;
}

vector<vector<double>> identity_matrix(int n) {
    vector<vector<double>> E(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i)
        E[i][i] = 1;
    return E;
}

vector<vector<double>> inversed(const vector<vector<double>>& matrix_A) {
    vector<vector<double>> inversed(matrix_A.size(), vector<double>(matrix_A.size()));
    double det = determinant(matrix_A);

    if (det == 0) {
        cerr << "Matrix is not invertible" << std::endl;
        return matrix_A;
    }

    int sign = 1;
    for (int i = 0; i < matrix_A.size(); i++) {
        for (int j = 0; j < matrix_A.size(); j++) {
            vector<vector<double>> minor = get_minor(matrix_A, i, j);
            double minor_det = determinant(minor);
            
            inversed[j][i] = sign * minor_det / det;
            sign *= -1;
        }
    }

    return inversed;
}

vector<vector<double>> multiplication_of_matrixes(const vector<vector<double>> matrix_A, const vector<vector<double>>matrix_B) {
    int len_A = matrix_A.size(), wid_A = matrix_A[0].size(), wid_B = matrix_B[0].size();
    vector<vector<double>> matrix_C(len_A, vector<double>(wid_B, 0));
    for (int i = 0; i < len_A; i++) {
        for (int j = 0; j < wid_B; j++) {
            double c;
            for (int k = 0; k < wid_A; k++) {
                c = matrix_A[i][k] * matrix_B[k][j];
            }
            matrix_C[i][j] = c;
        }
    }
    return matrix_C;
}
//
pair<vector<vector<double>>, vector<vector<double>>>  lu(vector<vector<double>> coef_matrix, vector<vector<double>> const_matrix)
{
    int N = coef_matrix.size(); 
    vector<vector<double>> L(N, vector<double>(N, 0)); 
    vector<vector<double>> U = coef_matrix;
    for(int i = 0; i < N; i++){
        for(int j = i; j < N; j++){
        L[j][i]=U[j][i]/U[i][i];
        }
    }
    
    for(int k = 1; k < N; k++){
        for(int i = k-1; i < N; i++){
            for(int j = i; j < N; j++){
                L[j][i]=U[j][i]/U[i][i];
            }
        }

        for(int i = k; i < N; i++){
            for(int j = k-1; j < N; j++){
                U[i][j]=U[i][j]-L[i][k-1]*U[k-1][j];
            }
        }
    }
    return make_pair(L, U);
}

vector<vector<double>> solutions(vector<vector<double>>& coef_matrix, vector<vector<double>>& const_matrinx) {
    pair<vector<vector<double>>, vector<vector<double>> > LU = lu(coef_matrix, const_matrinx);
    vector<vector<double>>  L = LU.first, U = LU.second;
    vector<vector<double>>  result = const_matrinx;
    int N = result[0].size();
    int M = coef_matrix.size();

    for (int k  = 0; k < N; k++) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < i; j++) {
                result[i][k] -= result[j][k] * L[i][j];
            }
        }
        for (int i = M - 1; i >= 0; i--) {
            for (int j = i + 1; j < M; j++) {
                result[i][k] -= result[j][k] * U[i][j];
            }
            result[i][k] /= U[i][i];
        }
    }

    return result;
}

int main() {
    vector<vector<double>> coef_matrix = {
            {-6, -5,  -3, -8},
            {5, -1, -5,  -4},
            {-6,  0,  5, 5},
            {-7,  -2, 8, 5}
    };
   vector<vector<double>> const_matrix = {
           {101},
            {51},
            {-53},
            {-63}
    };
    pair<vector<vector<double>>,vector<vector<double>>> LU = lu(coef_matrix, const_matrix);
    cout << "Solution of the system: " << endl;
    vector<vector<double>> solved = solutions(coef_matrix, const_matrix);
    print_matrix(solved);
    cout << endl;
    cout << "Determinant of the matrix = " << determinant(coef_matrix) << endl;
    cout << endl << "Inversed matrix = " << endl;
    vector<vector<double>> inversed_matrix = inversed(coef_matrix);
    print_matrix(inversed_matrix);
    return 0;
}

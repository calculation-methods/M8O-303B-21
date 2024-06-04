#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<double>> identity_matrix(int n){
    vector<vector<double>> matrix_I(n, vector<double>(n, 0));
     for(int i = 0; i < n; i++)
        matrix_I[i][i] = 1;
    return matrix_I;
}


vector<vector<double>> transponirovanie(vector<vector<double>> matrix_A){
    int len_A = matrix_A.size(), wid_A = matrix_A[0].size();
    vector<vector<double>> A_T(wid_A, vector<double>(len_A));
    for (int i=0; i<len_A; ++i)
        for (int j=0; j<wid_A; ++j)
            A_T[j][i] = matrix_A[i][j];
    return A_T;
}

vector<vector<double>> matrix_multiplication(vector<vector<double>> matrix_A, vector<vector<double>> matrix_B) {
    int len_A = matrix_A.size(), wid_A = matrix_A[0].size(), wid_B = matrix_B[0].size();
    vector<vector<double>> matrix_C(len_A, vector<double>(wid_B,0));
    for (int i = 0; i < len_A; i++) {
        for (int j = 0; j < wid_B; j++) {
            double c = 0;
            for (int k = 0; k < wid_A; k++)
               c += matrix_A[i][k] * matrix_B[k][j];
            matrix_C[i][j] = c;
        }
    }
    return matrix_C;
}

vector<vector<double>> U(vector<vector<double>> matrix_A){
    vector<vector<double>> u = identity_matrix(matrix_A.size());
    int i_max = 0, j_max = 1;
    double k = matrix_A[0][1];
    int len_A = matrix_A.size(), wid_A = matrix_A[0].size();
    for (int i = 0; i < len_A; ++i)
        for (int j = i+1; j < wid_A; ++j)
            if (abs(matrix_A[i][j]) > k) {
                k = abs(matrix_A[i][j]);
                i_max = i;
                j_max = j;
            }
    double phi = (matrix_A[i_max][i_max] == matrix_A[j_max][j_max]) ? atan(2*matrix_A[i_max][j_max]/(matrix_A[i_max][i_max] - matrix_A[j_max][j_max])) / 2 : 3.14/4;

    u[i_max][j_max] = -sin(phi);
    u[j_max][i_max] = sin(phi);
    u[i_max][i_max] = cos(phi);
    u[j_max][j_max] = cos(phi);
    return u;
}

double eps(const vector<vector<double>>& matrix1){
    int n=matrix1.size(), m=matrix1[0].size();
    double error = 0;
    for (int i=0; i<n; ++i)
        for (int j=i+1; j<m; ++j)
            error += matrix1[i][j]*matrix1[i][j];
    return sqrt(error);
}

pair<vector<double>, vector<vector<double>>> rotation_method(vector<vector<double>>& coeff_matrix, double EPS){
    int n = coeff_matrix.size();
    vector<vector<double>> eigenvectors = identity_matrix(n);
    while (eps(coeff_matrix) > EPS){
        vector<vector<double>> u = U(coeff_matrix);
        eigenvectors = matrix_multiplication(eigenvectors, u);
        vector<vector<double>> U_T = transponirovanie(u);
        coeff_matrix = matrix_multiplication(matrix_multiplication(U_T, coeff_matrix), u);
    }

    vector<double> eigenvalues(n);
    for (int i=0; i<n; ++i)
        eigenvalues[i] = coeff_matrix[i][i];
    return make_pair(eigenvalues, eigenvectors);
}

int main() {
    int n = 3; 
    vector<vector<double>> X = {
        {8, 0, -2},
        {0, 5, 4},
        {-2, 4, -6}};
    vector<vector<double>> Y = X;
    vector<double> eigenvalues;
    vector<vector<double>> eigenvectors;
    eigenvalues = rotation_method(X, 0.01).first;
    eigenvectors = rotation_method(Y, 0.01).second;
    cout << "Eigenalues:" << endl;
    for (double eigenvalue : eigenvalues) {
        cout << eigenvalue << " " << endl;
    }
    cout << endl;

    cout << "Eigenectors:" << endl << endl;
    for (int i = 0; i < eigenvectors.size(); ++i) {
        cout << "For eigenvalue = " << eigenvalues[i] << ", eigenector = [ ";
        for (double component : eigenvectors[i]) {
            cout << component << " ";
        }
        cout <<"]";
        cout << endl << endl;
    }
    return 0;
}
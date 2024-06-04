#include <iostream>
#include <vector>

using namespace std;

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

vector<vector<double>> transponirovanie(vector<vector<double>> matrix_A){
    int len_A = matrix_A.size(), wid_A = matrix_A[0].size();
    vector<vector<double>> A_T(wid_A, vector<double>(len_A));
    for (int i=0; i<len_A; ++i)
        for (int j=0; j<wid_A; ++j)
            A_T[j][i] = matrix_A[i][j];
    return A_T;
}

int sign(double a){
    if (a > 0)
        return 1;
    if (a < 0)
        return -1;
    return 0;
}


double get_eps(const vector<vector<double>> matrix_A){
    double eps = 0;
    int len_A = matrix_A.size();
    for(int i=0; i < len_A; i++)
        for(int j=0; j<i-1; j++)
            eps += matrix_A[i][j]*matrix_A[i][j];
    return sqrt(eps);
}

vector<vector<double>> Q_find(vector<vector<double>>C, int ind){
    int n = C.size();
    vector<vector<double>> v(n, vector<double>(1));

    for(int i=0; i<n; i++){
        if (i < ind)
            v[i][0] = 0;
        else if (i == ind){
            double sum = 0;
            for (int j=ind; j < n; j++)
                sum += C[j][i]*C[j][i];
            v[i][0] = C[i][i] + sign(C[i][i]) * sqrt(sum);
        }
        else
            v[i][0] = C[i][ind];   
    }

    vector<vector<double>> v_t = transponirovanie(v);
    double k = -matrix_multiplication(v_t, v)[0][0]/2;
    v = matrix_multiplication(v, v_t);
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            v[i][j] /= k;

    for (int i = 0; i < n; i++)
        v[i][i] += 1;
    return  v;
}


pair<vector<vector<double>>, vector<vector<double>>> QR_decomposition(vector<vector<double>> coeff){
    vector<vector<double>> coefs = coeff;
    vector<vector<double>> Q = Q_find(coefs, 0);
    coefs = matrix_multiplication(Q, coefs);
    int n = coefs.size();
    for (int i=1; i<n-1; i++){
        vector<vector<double>> H = Q_find(coefs, i);
        Q = matrix_multiplication(Q, H);
        coefs = matrix_multiplication(H, coefs);
    }
    return make_pair(Q, coefs);
}


vector<double> get_eigenvalues(vector<vector<double>> coefs, double EPS){
    while (get_eps(coefs) > EPS){
        pair<vector<vector<double>>, vector<vector<double>>> QR = QR_decomposition(coefs);
        coefs = matrix_multiplication(QR.second, QR.first);
    }
    int n = coefs.size();
    vector<double> result(n);
    for (int i = 0; i<n; i++)
        result[i] = coefs[i][i];
    return result;
}


int main() {
    vector<vector<double>> coefs{
        {-5, -8, 4},
        {4, 2, 6},
        {-2, 5, -6}
    };


    vector<double> eigenvalues = get_eigenvalues(coefs, 0.01);
    int n = eigenvalues.size();

    for (int i = 0; i < n; i++)
        cout << "eigenvalue " << i << " = " << eigenvalues[i] << endl;

    return 0;
}
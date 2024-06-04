#include <bits/stdc++.h>

using namespace std;

namespace nfunc {
    double f1(double x1, double x2) {
        return x1 - cos(x2) - 1;
    }
    double f2(double x1, double x2) {
        return x2 - log(x1 + 1) - 3;
    }
    double df1_dx1(double x1, double x2){
        return 1; 
    }
    double df1_dx2(double x1, double x2){ 
        return -sin(x2); 
    }
    double df2_dx1(double x1, double x2){
        return 1/(x1 + 1);
    }
    double df2_dx2(double x1, double x2){
        return 1;
    }
}

namespace sifunc {
    double phi1(double x1, double x2) {
        return 1 + cos(x2);
    }
    double phi2(double x1, double x2) {
        return 3 + log(x1 + 1);
    }
    double dphi1_dx1(double x2) {
        return 0;
    }
    double dphi1_dx2(double x2) {
        return -sin(x2);
    }
    double dphi2_dx1(double x1) {
        return 1.0 / (x1 + 1);
    }
    double dphi2_dx2(double x1) {
        return 0;
    }
}

double eps(const vector<double>& vect1, const vector<double>& vect2, double q) {
    double d = 0.0;
    for(int i = 0; i < vect1.size(); i++)
        d = max(d, abs(vect1[i] - vect2[i]));
    if (q == -1)
        return d;
    return q*d/(1-q);
}

double determinant(double x1, double x2, vector<vector<function<double(double, double)>>>& matrix) {
    return matrix[0][0](x1, x2) * matrix[1][1](x1, x2) - matrix[0][1](x1, x2) * matrix[1][0](x1, x2);
}


tuple<double, double, int> newton(double start_value_1, double start_value_2, double EPS) {   
    vector<vector<function<double(double, double)>>> J = {{nfunc::df1_dx1, nfunc::df1_dx2}, {nfunc::df2_dx1, nfunc::df2_dx2}};
    vector<vector<function<double(double, double)>>> A_1 = {{nfunc::f1, nfunc::df1_dx2}, {nfunc::f2, nfunc::df2_dx2}};
    vector<vector<function<double(double, double)>>> A_2 = {{nfunc::df1_dx1, nfunc::f1}, {nfunc::df2_dx1, nfunc::f2}};

    int counter = 0;
    double x_next_1, x_next_2, x_curr_1 = start_value_1, x_curr_2 = start_value_2;
    x_next_1 = start_value_1 - determinant(start_value_1, start_value_2, A_1)/determinant(start_value_1, start_value_2, J);
    x_next_2 = start_value_2 - determinant(start_value_1, start_value_2, A_2)/determinant(start_value_1, start_value_2, J);

    while (eps({x_curr_1, x_curr_2}, {x_next_1, x_next_2}, -1) >= EPS){
        counter += 1;
        
        x_curr_1 = x_next_1;
        x_curr_2 = x_next_2;

        x_next_1 = x_next_1 - determinant(x_next_1, x_next_2, A_1)/determinant(x_next_1, x_next_2, J);
        x_next_2 = x_next_2 - determinant(x_next_1, x_next_2, A_2)/determinant(x_next_1, x_next_2, J);
    }

    return {x_next_1, x_next_2, counter};
}


tuple<double, double, int> simple_iter(double start_value_1, double start_value_2, double q, double EPS) {
    int counter = 0; 
    double x_next_1 = start_value_1, x_next_2 = start_value_2, x_curr_1 = start_value_1*5, x_curr_2 = start_value_2*5;

    while (eps({x_curr_1, x_curr_2}, {x_next_1, x_next_2}, q) >= EPS){
        counter += 1;

        x_curr_1 = x_next_1;
        x_curr_2 = x_next_2;

        x_next_1 = sifunc::phi1(x_next_1, x_next_2);
        x_next_2 = sifunc::phi2(x_next_1, x_next_2);
    }
    return {x_next_1, x_next_2, counter};
}


double convergence(double max_dphi1, double max_dphi2) {
    double row1 = fabs(sifunc::dphi1_dx1(max_dphi1)) + fabs(sifunc::dphi1_dx2(max_dphi1));
    double row2 = fabs(sifunc::dphi2_dx1(max_dphi2)) + fabs(sifunc::dphi2_dx2(max_dphi2));
    return max(row1, row2);
}


int main(){
    double epsillon = 0.00001, res_1, res_2;
    int counter;

    double q = convergence(0.5, 2.5);

    tie(res_1, res_2, counter) = newton(0.0, 3.0, epsillon);
    cout << endl << "Newton method" << endl << "x1 = " << res_1 << endl << "x2 = " << res_2 << endl << "Iteration count = " << counter << endl << endl;

    tie(res_1, res_2, counter) = simple_iter(0.0, 3.0, 0.7, epsillon);
    cout << "Simple iterations method" << endl << "x1 = " << res_1 << endl << "x2 = " << res_2 << endl << "Iteration count = " << counter << endl << endl;

    return 1;
}
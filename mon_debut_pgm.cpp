#include <iostream>
#include <cmath>

using namespace std;

double f(double a, double d, double l, double h) {
    return sin(a) - (d - l * cos(a))/h;
}

double findRoot(double d, double l, double h) {
    double a0 = 0.0; // borne inférieure
    double a1 = M_PI/2; // borne supérieure
    double tol = 1e-1; // tolérance
    double a = (a0 + a1)/2.0; // valeur initiale
    while (fabs(f(a, d, l, h)) > tol) {
        if (f(a, d, l, h) > 0) {
            a1 = a;
        } else {
            a0 = a;
        }
        a = (a0 + a1)/2.0;
    }
    return a;
}

int main() {
    double d = 1.0;
    double l = 0.25;
    double h = 3.0;
    double a = findRoot(d, l, h);
    cout << "Angle a = " << a << endl;
    return 0;
}


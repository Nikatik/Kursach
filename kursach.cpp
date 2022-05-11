#include "probe.hpp"
#include <cstdlib>
#include <iostream>
#include <time.h>

using namespace std;

int main()
{
    double I = 300.0, P = 350.0, z, V, M;
    double g = 1.634, tol3, tol2, tol1;

    long double* t1 = new long double[3];
    long double* t2 = new long double[3];

    bool drop = 0;

    while (drop != 1)
    {
        // get info
        // if (vertical_period == 1)
        drop = 1;
    }

    // x1 = z;
    // x2 = V;
    // a = P / (g * I);
    // x1 = k*a^2/(3*M^2)*t1^3+(k*a/(2*M)-g/2)*t1^2
    // x2 = -k*a^3/(3*M^3)*t2^3 - k*a^2/(3*M^2)*t2^2 + (g*M-k*a)/M*t2
    // t1-t2<tol1

    cout << "Hello World!\n";

    return 0;
}

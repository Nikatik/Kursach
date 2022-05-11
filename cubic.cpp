/* Cubic equation solution. Real coefficients case.

   int Cubic(double *x,double a,double b,double c);
   Parameters:
   x - solution array (size 3). On output:
       3 real roots -> then x is filled with them;
       1 real + 2 complex -> x[0] is real, x[1] is real part of
                             complex roots, x[2] - non-negative
                             imaginary part.
   a, b, c - coefficients, as described
   Returns: 3 - 3 real roots;
            1 - 1 real root + 2 complex;
            2 - 1 real root + complex roots imaginary part is zero
                (i.e. 2 real roots).
*/

#include "probe.hpp"
// #define M_PI (3.141592653589793)
#define M_2PI (2. * M_PI)

int cubic (long double* x, long double a, long double b, long double c)
{
    long double q, r, r2, q3;

    q  = (a * a - 3. * b) / 9.;
    r  = (a * (2. * a * a - 9. * b) + 27. * c) / 54.;
    r2 = r * r;
    q3 = q * q * q;

    if (r2 < q3)
    {
        long double t = acos (r / sqrt (q3));

        a /= 3.;
        q = -2. * sqrt (q);

        x[0] = q * cos (t / 3.) - a;
        x[1] = q * cos ((t + M_2PI) / 3.) - a;
        x[2] = q * cos ((t - M_2PI) / 3.) - a;

        return (3);
    }
    else
    {
        long double aa, bb;

        if (r <= EPS)
        {
            r = -r;
        }

        aa = -pow (r + sqrt (r2 - q3), 1. / 3.);

        if (fabs (aa) > EPS)
        {
            bb = q / aa;
        }
        else
        {
            bb = 0.;
        }

        a /= 3.;
        q = aa + bb;
        r = aa - bb;

        x[0] = q - a;
        x[1] = (-0.5) * q - a;
        x[2] = (sqrt (3.) * 0.5) * fabs (r);

        if (fabs (x[2]) < EPS)
        {
            return (2);
        }

        return (1);
    }
}

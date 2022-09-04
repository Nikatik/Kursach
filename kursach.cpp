/*
    return:
        -3: software error
        -2: incorrect input
        -1: vehical crashed
         0: vehical landed
         1: help printed
*/
#include "probe.hpp"
#include "random.hpp"

#define delta_time 1e-6

#define tr 1        // trace trajectory
#define mode 1

#define tt 0.2

int main (int argc, char* argv[])
{

    double I = 300.0;
    double g = 1.634;
    double G = 9.80665;
    double P = 350.0;

    double tol1     = 0.001;
    double tol2     = 0.5;
    double tol3     = 2.;
    double tol_prev = 1e10;

    double M = 100.;
    double z = 1000.;
    double V = -30.;
    double M0;
    double z0;
    double V0;

    double a     = P / (G * I);
    double k     = G * I;
    double time  = 0;
    double dtime = 0;
    double ttime = 0;
    double ftime = 0;
    double x1;
    double x2;

    long double* t1;
    long double* t2;
    try
    {
        t1 = new long double[6];
        t2 = new long double[6];
    }
    catch (const bad_alloc& e)
    {
        printf ("ERROR: Software error: memory error!!!\n");
        return -3;
    }

    bool drop       = false;
    bool end        = false;
    bool full_trust = false;
    bool repeat     = false;

    int elem = 0;

    int res;
    int res2;

    switch (arg_pars (argc, argv, tol1, tol2, tol3, M, z, V))
    {
        case -2:
            delete[] t1;
            delete[] t2;

            return -2;

        case 0:
            break;

        case 1:
            delete[] t1;
            delete[] t2;

            return 1;

        default:
            delete[] t1;
            delete[] t2;

            printf ("\nHow had you done this?\n");
            return -3;
    }

    M0 = M;
    z0 = z;
    V0 = V;

    if (!drop)
    {
        while (z > 0)
        {
            // get info
            z = z + V * delta_time;
            V = V - g * delta_time;

            if (V < 0. && z > 0)
            {
                // drop = true;
                break;
            }

            if (z <= 0)
            {
                if (fabs (V) < tol3)
                {
                    printf ("Vehical already landed!\nStopping...\n");

                    delete[] t1;
                    delete[] t2;

                    return 0;
                }
                if (fabs (V) > tol3 && V < 0)
                {
                    printf ("Vehical crashed!\nStopping...\n");

                    delete[] t1;
                    delete[] t2;

                    return -1;
                }
            }
        }
    }

    x1 = z;
    x2 = V;
    for (dtime = 0; x1 > tol2 || fabs (x2) > tol3; dtime += delta_time)
    {
        ftime += delta_time;

        if (x1 <= 0 || M < 0)
        {
            break;
        }

        if (!full_trust)
        {
            if (!repeat)
            {
                z      = x1;
                V      = x2;
                repeat = true;
                dtime  = 0;
            }

            x1 = height (1e10, V, z, g, 1, 0, dtime);
            x2 = velocity (1e10, V, g, 0, 0, dtime);

            if (!end && x2 < -tol3)
            {
                _Pragma ("GCC diagnostic push") _Pragma (
                    "GCC diagnostic ignored \"-Wimplicit-fallthrough=\"")

                    switch (mode)
                {
                    case 2:
                        if (fabs (ftime * tt - static_cast<int> (ftime * tt)) <
                            delta_time * tt)
                        {
                            if (probe (1000) % 2 == 1)
                            {
                                full_trust = true;
                                time -= dtime;
                                t1[3] = t2[3] = 1 / tt;
                            }
                            else
                            {
                                t1[3] = t2[3] = 0;
                            }
                        }
                        break;
                    case 3:
                        if (fabs (ftime * tt - static_cast<int> (ftime * tt)) <
                            delta_time * tt)
                        {
                            P = static_cast<double> (probe (1000) % 14) *
                                    (350. / 15.) +
                                350. / 15.;
                            a        = P / (G * I);
                            tol_prev = 1e10;
                        }
                    default:

                        for (int i = 3; i < 6; i++)
                        {
                            t1[i] = -1.;
                            t2[i] = -1.;
                        }

                        res = cubic (t1,
                                     ((3. * (P - g * M) * M) / (2 * P * a)),
                                     0.,
                                     ((3. * pow (M, 2.) * (-x1)) / (P * a)));

                        elem = 0;
                        for (int i = 0; i < res; i++)
                        {
                            if (t1[i] >= EPS)
                            {
                                t1[3 + elem] = t1[i];
                                elem++;
                            }
                        }
                        t1[3] = max (max (t1[3], t1[4]), t1[5]);

                        elem = 0;
                        res2 = cubic (
                            t2,
                            ((M) / (a)),
                            (3. * (P - g * M) * pow (M, 2.)) /
                                (P * pow (a, 2.)),
                            ((3. * pow (M, 3.) * x2) / (P * pow (a, 2.))));

                        for (int i = 0; i < res2; i++)
                        {

                            if (t2[i] >= EPS)
                            {
                                t2[3 + elem] = t2[i];
                                elem++;
                            }
                        }
                        t2[3] = max (max (t2[3], t2[4]), t2[5]);

                        if (fabs (t1[3] + 1) < EPS || fabs (t2[3] + 1) < EPS)
                        {

                            if (tr == 1)
                            {
                                print_trajectory (x1,
                                                  x2,
                                                  ftime,
                                                  t1[3],
                                                  t2[3],
                                                  full_trust,
                                                  delta_time);
                            }

                            continue;
                        }

                        if (t2[3] - t1[3] > tol3)
                        {
                            full_trust = true;
                            time -= dtime;
                        }

                        if (fabs (t1[3] - t2[3]) < tol1 ||
                            fabs (t1[3] - t2[3]) > tol_prev)
                        {
                            full_trust = true;
                            time -= dtime;
                        }
                        else
                        {
                            tol_prev =
                                static_cast<double> (fabs (t1[3] - t2[3]));
                        }
                }
                _Pragma ("GCC diagnostic pop")
            }
        }
        else
        {
            if (repeat)
            {
                z        = x1;
                V        = x2;
                tol_prev = 1e10;
                repeat   = false;
            }

            x1 = height (M, V, z, g, a, k, dtime + time);
            x2 = velocity (M, V, g, a, k, dtime + time);

            if (x2 > tol1 ||
                fabs (dtime + time - max (t1[3], t2[3])) < delta_time)
            {
                time += dtime;
                M = M - a * time;
                ttime += time;
                time       = 0;
                full_trust = false;
                // end        = true;
            }

            if (mode != 1 && mode != 2)
            {

                if (fabs (ftime * tt - static_cast<int> (ftime * tt)) <
                    delta_time * tt)
                {
                    P = static_cast<double> (probe (1000) % 14) * (350. / 15.) +
                        350. / 15.;
                    a = P / (G * I);
                    time += dtime;
                    M = M - a * time;
                    ttime += time;
                    time       = 0;
                    full_trust = false;
                }
            }
        }

        if (tr == 1)
        {
            print_trajectory (
                x1, x2, ftime, t1[3], t2[3], full_trust, delta_time);
        }
    }
    if (full_trust)
    {
        time += dtime;
        M = M - a * time;
        ttime += time;
        // full_trust = false;
    }

    if (print_result (M0, z0, V0, ttime, x1, x2, M0 - M, ftime, tol3) == -1)
    {

        delete[] t1;
        delete[] t2;

        return -1;
    }

    delete[] t1;
    delete[] t2;

    return 0;
}

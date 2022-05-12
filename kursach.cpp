/*
    return:
        -3: software error
        -2: incorrect input
        -1: vehical crashed
         0: vehical landed
         1: help printed
*/
#include "probe.hpp"
#define delta_time 1e-4

int main (int argc, char* argv[])
{

    double I = 300.0;
    double g = 1.634;
    double P = 350.0;

    double tol1     = 0.001;
    double tol2     = 0.5;
    double tol3     = 2.;
    double tol_prev = 1e10;

    double M  = 100.;
    double z  = 1000.;
    double V  = -30.;
    double z0 = 1000.;
    double V0 = -30.;

    double a     = P / (g * I);
    double k     = g * I;
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
        t1 = new long double[4];
        t2 = new long double[4];
    }
    catch (const bad_alloc& e)
    {
        cout << "ERROR: Software error: memory error!!!" << endl;
        return -3;
    }

    bool drop       = false;
    bool end        = false;
    bool full_trust = false;
    bool repeat     = false;

    int error = 0;

    if (argc >= 2)
    {
        switch (argv[1][0])
        {
            case '0':
                M = 0;
                while (M <= 0)
                {
                    cout << "Print start mass: ";
                    cin >> M;
                    if (M <= 0)
                    {
                        cout << "Your input is not correct! Use -h for help..."
                             << endl;
                    }
                    cout << endl;
                }

                z = -100;
                while (z < 0)
                {
                    cout << "Print start height: ";
                    cin >> z;
                    if (z < 0)
                    {
                        cout << "Your input is not correct! Use -h for help..."
                             << endl;
                    }
                    cout << endl;
                }

                cout << "Print start velocity: ";
                cin >> V;
                cout << endl;

                break;

            case '1':
                if (argc >= 3)
                {
                    if (atof (argv[2]) > 0)
                    {
                        M = atof (argv[2]);
                    }
                    else
                    {
                        cout << "Your input is not correct! Use -h for help..."
                             << endl;
                        return -2;
                    }
                }

                if (argc >= 4)
                {
                    if (atof (argv[3]) > 0)
                    {
                        z = atof (argv[3]);
                    }
                    else
                    {
                        cout << "Your input is not correct! Use -h for help..."
                             << endl;
                        return -2;
                    }
                }

                if (argc >= 5)
                {
                    V = atof (argv[4]);
                }

                break;

            case '2':
                if (argc == 8)
                {
                    tol1 = atof (argv[2]);
                    tol2 = atof (argv[3]);
                    tol3 = atof (argv[4]);
                    M    = atof (argv[5]);
                    z    = atof (argv[6]);
                    V    = atof (argv[7]);
                    if (tol1 < 0 || tol2 < 0 || tol3 < 0 || M <= 0 || z < 0)
                    {
                        cout << "Your input is not correct! Use -h for help..."
                             << endl;
                        return -2;
                    }
                }
                else
                {
                    cout << "Your input is not correct! Use -h for help..."
                         << endl;
                    return -2;
                }
                break;
            default:
                print_help();
                return 1;
        }
    }

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
                    cout << "Vehical already landed!" << endl
                         << "Stopping..." << endl;

                    delete[] t1;
                    delete[] t2;

                    return 0;
                }
                if (fabs (V) > tol3 && V < 0)
                {
                    cout << "Vehical crashed!" << endl << "Stopping..." << endl;

                    delete[] t1;
                    delete[] t2;

                    return -1;
                }
            }
        }
    }
    x1 = z;
    x2 = V;

    // t1^3+(((k * a) / (2 * M) - g / 2)/((k * a^2) / (3 * M^2))) * t1^2 -
    // x1/((k * a^2) / (3 * M^2)) = 0

    // t2^3 + (M / a) * t2^2 + (g * M - k * a) * t2 / ((-k * a^3) / (3 * M^2)) -
    // x2 / ((-k * a^3) / (3 * M^3)) = 0

    // t1 - t2 < tol1

    for (dtime = 0; x1 > tol2; dtime += delta_time)
    {
        ftime += delta_time;
        if (!full_trust)
        {
            if (!repeat)
            {
                z      = x1;
                V      = x2;
                repeat = true;
                dtime  = 0;
            }
            x1    = z + V * dtime - g * pow (dtime, 2.) / 2.;
            x2    = V - g * dtime;
            t1[3] = -1.;
            t2[3] = -1.;
            if (!end && fabs (x2) > tol1)
            {
                int res =
                    cubic (t1,
                           (((k * a) / (2. * M) - g / 2.) /
                            ((k * pow (a, 2.)) / (3. * pow (M, 2.)))),
                           0.,
                           (-x1 / ((k * pow (a, 2.)) / (3. * pow (M, 2.)))));
                for (int i = 0; i < res; i++)
                {
                    if (t1[i] >= EPS)
                    {
                        t1[3] = t1[i];
                    }
                }

                int res2 =
                    cubic (t2,
                           M / a,
                           3. * (P - g * M) * pow (M, 2.) / (k * pow (a, 3.)),
                           3. * pow (M, 3.) * x2 / (k * pow (a, 3.)));
                for (int i = 0; i < res2; i++)
                {
                    if (t2[i] >= EPS)
                    {
                        t2[3] = t2[i];
                    }
                }

                if (error > 1000)
                {
                    cout << "ERROR: Software error: floating point counting;"
                         << endl;
                    return -3;
                }
                if (fabs (t1[3] + 1) < EPS || fabs (t2[3] + 1) < EPS)
                {
                    // error++;
                    continue;
                }

                if (fabs (t1[3] - t2[3]) < tol1 ||
                    fabs (t1[3] - t2[3]) > tol_prev)
                {
                    // cout<<t1[3]<<" "<<t2[3]<<endl;
                    full_trust = true;
                    time -= dtime;
                }
                else
                {
                    tol_prev = static_cast<double> (fabs (t1[3] - t2[3]));
                }
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

            x2 = -k * log (1 - a * (dtime + time) / M) - g * (dtime + time) + V;
            x1 = (k * (M - a * (dtime + time)) *
                  log (1 - a * (dtime + time) / M)) /
                     a -
                 g * pow ((dtime + time), 2.) / 2. + k * (dtime + time) +
                 V * (dtime + time) + z;

            if (x2 > tol1 ||
                fabs (dtime + time - max (t1[3], t2[3])) < delta_time)
            {
                time += dtime;
                ttime += time;
                time       = 0;
                full_trust = false;
                // end        = true;
            }
        }

        if (fabs (ftime - static_cast<int> (ftime)) < delta_time)
        {
            printf (
                "Высота: %7.3lf;\tСкорость: %7.2lf;\tВремя: %2.0lf;\t Полная "
                "тяга: ",
                x1,
                x2,
                ftime);
            if (full_trust)
            {
                printf ("yes\n");
            }
            else
            {
                printf (" no\n");
            }
        }
    }

    if (full_trust)
    {
        cout << "hey" << endl;
        time += dtime;
        ttime += time;
        // full_trust = false;
    }

    printf ("\nstart mass | start height | start velocity | fulltrust time | "
            "ending speed | used fuel | end height | full time\n%10.3lf | %12.3lf | "
            "%14.5lf | %14.4lf | "
            "%12.6lf | %9.3lf | %10.5lf | %9.4lf\n\n",
            M,
            z0,
            V0,
            ttime,
            x2,
            a * ttime,
            x1,
            ftime);

    if (fabs (x2) < tol3)
    {
        cout << "Vehical successfully landed!" << endl;

        delete[] t1;
        delete[] t2;

        return 0;
    }
    if (fabs (x2) >= tol3 && x2 < 0)
    {
        cout << "Vehical crashed!" << endl;

        delete[] t1;
        delete[] t2;

        return -1;
    }

    delete[] t1;
    delete[] t2;

    return 0;
}

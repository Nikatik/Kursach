/*
    return:
        -3: software error
        -2: incorrect input
        -1: vehical crashed
         0: vehical landed
         1: help printed
*/
#include "probe.hpp"
#include <cstdlib>
#include <iostream>
#include <time.h>
#define delta_time 1e-2
using namespace std;

int main (int argc, char* argv[])
{

    double I = 300.0;
    double g = 1.634;
    double P = 350.0;

    double tol1 = 0.5;
    double tol2 = 0.03;
    double tol3 = 0.2;

    double M = 100.;
    double z = 1000.;
    double V = -30.;

    double a    = P / (g * I);
    double k    = g * I;
    double time = 0;
    double x1;
    double x2;

    long double* t1;
    long double* t2;
    try
    {
        t1 = new long double[3];
        t2 = new long double[3];
    }
    catch (const bad_alloc& e)
    {
        cout << "ERROR: software error!!!" << endl;
        return -3;
    }

    bool drop = 0;

    if (argc >= 2)
    {
        switch (atoi (argv[1]))
        {
            case 0:
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

            case 1:
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

            case 2:
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
                // print_help();
                return 1;
        }
    }

    if (drop != 1)
    {
        while (z > 0)
        {
            // get info
            z = z + V * delta_time;
            V = V - g * delta_time;

            if (V < 0. && z > 0)
            {
                drop = 1;
                break;
            }

            if (z <= 0)
            {
                if (fabs (V) < tol1)
                {
                    cout << "Vehical already landded!" << endl
                         << "Stopping..." << endl;
                    return 0;
                }
                if (fabs (V) > tol1 && V < 0)
                {
                    cout << "Vehical crashed!" << endl << "Stopping..." << endl;
                    return -1;
                }
            }
        }
    }

    // t1^3+(((k * a) / (2 * M) - g / 2)/((k * a^2) / (3 * M^2))) * t1^2 -
    // x1/((k * a^2) / (3 * M^2)) = 0

    // t2^3 + (M / a) * t2^2 + (g * M - k * a) * t2 / ((-k * a^3) / (3 * M^2)) -
    // x2 / ((-k * a^3) / (3 * M^3)) = 0

    // t1 - t2 < tol1

    for (time = 0; time < 20; time += 0.1)
    {
        x1 = z + V * time - g * pow (time, 2.) / 2.;
        x2 = V - g * time;

        int res = cubic (t1,
                         (((k * a) / (2. * M) - g / 2.) /
                          ((k * pow (a, 2.)) / (3. * pow (M, 2.)))),
                         0.,
                         (-x1 / ((k * pow (a, 2.)) / (3. * pow (M, 2.)))));
        cout << res << "  Высота = " << x1 << "; Время: ";
        for (int i = 0; i < 3; i++)
            cout << " " << t1[i];
        cout << endl;

        int res2 = cubic (
            t2,
            (((k * pow (a, 2.)) / (3 * pow (M, 2.))) /
             ((k * pow (a, 3.)) / (3 * pow (M, 3.)))),
            ((g * M - k * a) / ((-k * pow (a, 3.)) / (3. * pow (M, 2.)))),
            (-x2 / ((-k * pow (a, 3.)) / (3. * pow (M, 3.)))));

        cout << res2 << "  Скорость = " << x2 << "; Время: ";
        for (int i = 0; i < 3; i++)
            cout << " " << t2[i];
        cout << endl;

        cout << endl;
    }

    delete[] t1;
    delete[] t2;

    return 0;
}

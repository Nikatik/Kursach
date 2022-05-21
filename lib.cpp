/*
        Service file for service functions. Child of code refactoring and
   formating.
*/
#include "probe.hpp"

/*
        Parsing argument string.

        return:
                -2 - invalid arguments
                 0 - successfully finished
                 1 - print help info

*/
int arg_pars (int argc,
              char* argv[],
              double& tol1,
              double& tol2,
              double& tol3,
              double& M,
              double& z,
              double& V)
{
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
    return 0;
}

double
height (double M, double V, double z, double g, double a, double k, double time)
{
    return ((k * (M - a * time) * log (1 - a * time / M)) / a -
            g * pow (time, 2.) / 2. + k * time + V * time + z);
}

double velocity (double M, double V, double g, double a, double k, double time)
{
    return (-k * log (1 - a * time / M) - g * time + V);
}
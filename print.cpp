/*
        Printing file for all printing functions.
*/
#include "probe.hpp"

void print_help (void)
{
    cout << "You start program for calculating vertical landing stage..."
         << endl
         << "There are three using episodes:" << endl
         << "\n    Start without any arguments:\n        ./program\n        "
            "Program will "
            "calculate test trajectory with prescribed parametrs."
         << endl
         << "\n    Start with one zero argument:\n        ./program 0\n        "
            "Program "
            "will ask you realtime input of mass, height and velocity."
         << endl
         << "\n\n    Start with many nonzero arguments:\n        1: ./program "
            "1 100 "
            "1000 -30\n            Program will read your arguments in a "
            "certain "
            "order:\n              mass, height, velocity\n\n        2: "
            "./program 2 0.01 0.01 0.2 "
            "100 1000 -30\n            !!! This is advanced option, don`t use "
            "it "
            "!!!\n            Program will read your arguments in a certain "
            "order:\n              "
            "tolerance(1), tol(2), tol(3), mass, height, velocity\n           "
            " ! All "
            "arguments are requered in this episode !"
         << endl
         << endl
         << endl
         << "All rights are reserved.\nGNUv3.\nThe author and implimenter is "
            "Sergeev Nikita, MSU, Departament of Mechanics and Mathematics."
         << endl;
}

void print_trajectory (double height,
                       double speed,
                       double full_time,
                       long double height_time,
                       long double speed_time,
                       bool full_trust,
                       double delta_time)
{
    if (fabs (full_time - static_cast<int> (full_time)) < delta_time)
    {
        printf ("Высота: %9.3lf;      Скорость: %7.2lf;      Время: %4.0lf c;  "
                "    Время_в: %7.3lf;      Время_с: %7.3lf;      Полная тяга: ",
                height,
                speed,
                full_time,
                static_cast<double> (height_time),
                static_cast<double> (speed_time));
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

void print_result (double start_mass,
                   double start_height,
                   double start_speed,
                   double trust_time,
                   double end_height,
                   double end_speed,
                   double fuel_mass,
                   double full_time)
{
    printf (
        "\nstart mass | start height | start velocity | fulltrust time | end "
        "height | ending speed | used fuel | full time\n%10.3lf | %12.3lf | "
        "%14.5lf | %14.4lf | %10.5lf | %12.6lf | %9.3lf | %9.4lf\n\n",
        start_mass,
        start_height,
        start_speed,
        trust_time,
        end_height,
        end_speed,
        fuel_mass,
        full_time);
}

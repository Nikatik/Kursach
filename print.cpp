/*
        Printing file for all printing functions.
*/
#include "probe.hpp"

#define mk 1        // output header

#define tt 2

void print_help (void)
{
    printf (
        "You start program for calculating vertical landing stage...\nThere "
        "are three using episodes:\n\n    Start without any arguments:\n       "
        " ./kursach\n        Program will calculate test trajectory with "
        "prescribed parametrs.\n\n    Start with one zero argument:\n        "
        "./kursach 0\n        Program will ask you realtime input of mass, "
        "height and velocity.\n\n\n    Start with many nonzero arguments:\n    "
        "    1: ./kursach 1 100 1000 -30\n            Program will read your "
        "arguments in a certain order:\n              mass, height, "
        "velocity\n\n        2: ./kursach 2 0.01 0.01 0.2 100 1000 -30\n       "
        "     !!! This is advanced option, don`t use it !!!\n            "
        "Program will read your arguments in a certain order:\n              "
        "tolerance(1), tol(2), tol(3), mass, height, velocity\n            ! "
        "All arguments are requered in this episode !\n\n\nAll rights are "
        "reserved.\nGNUv3.\nThe author and implimenter is Sergeev Nikita, MSU, "
        "Departament of Mechanics and Mathematics.\n");
}

void print_trajectory (double height,
                       double speed,
                       double full_time,
                       long double height_time,
                       long double speed_time,
                       bool full_trust,
                       double delta_time)
{
    if (fabs (full_time * tt - static_cast<int> (full_time * tt)) <
        delta_time * tt)
    {
        printf ("Высота: %9.3lf;      Скорость: %7.2lf;      Время: %9.3lf c;  "
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

int print_result (double start_mass,
                  double start_height,
                  double start_speed,
                  double trust_time,
                  double end_height,
                  double end_speed,
                  double fuel_mass,
                  double full_time,
                  double tolerance)
{
    if (mk == 1)
    {
        printf ("\nstart mass | start height | start velocity | fulltrust time "
                "| end "
                "height | ending speed | used fuel | full time | landed\n");
    }
    printf ("%10.3lf | "
            "%12.3lf | "
            "%14.5lf | %14.4lf | %10.5lf | %12.6lf | %9.3lf | %9.4lf ",
            start_mass,
            start_height,
            start_speed,
            trust_time,
            end_height,
            end_speed,
            fuel_mass,
            full_time);
    if (fabs (end_speed) >= tolerance && end_speed < 0)
    {
        printf ("|   no\n");
        return -1;
    }
    printf ("|   yes\n");
    if (mk == 1)
    {
        printf ("\n");
    }
    return 0;
}

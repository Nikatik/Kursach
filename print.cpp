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
            "./program 2 0.5 0.03 0.2 "
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
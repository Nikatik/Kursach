#ifndef PROBE_H_INCLUDED
#define PROBE_H_INCLUDED

#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

#define EPS 1e-10

// cubic.cpp
int cubic (long double* x, long double a, long double b, long double c);

// lib.cpp
int arg_pars (int argc,
              char* argv[],
              double& tol1,
              double& tol2,
              double& tol3,
              double& M,
              double& z,
              double& V);

double height (
    double M, double V, double z, double g, double a, double k, double time);

double velocity (double M, double V, double g, double a, double k, double time);

// print.cpp
void print_help (void);

void print_trajectory (double height,
                       double speed,
                       double full_time,
                       long double height_time,
                       long double speed_time,
                       bool full_trust,
                       double delta_time);

int print_result (double start_mass,
                  double start_height,
                  double start_speed,
                  double trust_time,
                  double end_height,
                  double end_speed,
                  double fuel_mass,
                  double full_time,
                  double tolerance);

#endif
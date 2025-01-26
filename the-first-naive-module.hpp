//This program discribes the first naive module.
//in which the stairs are influenced by frequency of people walking on them.

//In this module, we only consider the influence if the last-time walking.

#include <bits/stdc++.h>
using namespace std;

double delta_y_0 ;

double Calculate_k(double delta_t);

double Calculate_delta_y(double t_1, double t_2)
{
    return delta_y_0 * ( 1 + Calculate_k(abs(t_2-t_1)) );
}
//This program discribes the first naive module.
//in which the stairs are influenced by frequency of people walking on them.

//In this module, we only consider the influence if the last-time walking.

#include <bits/stdc++.h>
using namespace std;

double delta_y_0 ;

double Calculate_k(vector<double> time_vector);

double Calculate_delta_y(vector<double> time_vector)
{
    int n = time_vector.size();
    vector<double> V;
    double k = 0;
    for(int i=0;i<n;i++)
    {
        V.push_back(time_vector[i]);
        k+=Calculate_k(V);
    }
    return delta_y_0 * ( 1 + k );
}
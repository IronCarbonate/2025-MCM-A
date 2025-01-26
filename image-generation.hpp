#include <bits/stdc++.h>
using namespace std;

double c=100;
int length =100;

double gauss_function(double x, double mu, double sigma)
{
    return (1/(sigma*sqrt(2*M_PI))) * exp(-0.5*pow((x-mu)/sigma,2));
}

vector <double> function_generation(double mu_1,double sigma_1,double mu_2,double sigma_2)
{
    //x varies from -100 to 100
    //take 1.0 as the interval
    vector <double> Function;
    for(int i=-length;i<=length;i++)
    {
        Function.push_back(gauss_function(i,mu_1,sigma_1) + gauss_function(i,mu_2,sigma_2));
    }
    return Function;
}

double generateRandomDouble(double a) {
    std::mt19937 gen(static_cast<unsigned int>(time(nullptr)));
    std::normal_distribution<double> dis(0.0, a);

    return dis(gen);
}

double noise_generation(double y)
{
    return generateRandomDouble(c*sqrt(y));
}

vector <double> image_generation(vector <double> Function)
{
    //x varies from -100 to 100
    //take 1.0 as the interval
    vector <double> Image;
    for(int i=-length;i<=length;i++)
    {
        Image.push_back(Function[i+length] + noise_generation(Function[i+length]));
    }
    return Image;
}
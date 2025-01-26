#include <bits/stdc++.h>
#include "image-generation.hpp"
using namespace std;

vector<double> movingAverage(const std::vector<double>& data, int windowSize) {
    std::vector<double> result;
    for (size_t i = 0; i < data.size(); ++i) {
        double sum = 0.0;
        int count = 0;
        for (int j = -windowSize / 2; j <= windowSize / 2; ++j) {
            size_t index = i + j;
            if (index >= 0 && index < data.size()) {
                sum += data[index];
                ++count;
            }
        }
        result.push_back(sum / count);
    }
    return result;
}

int find_Peak(vector<double> data)
{
    int n = data.size();
    int peak = 0;
    for(int i=1;i<n-1;i++)
    {
        if(data[i]>data[i-1] && data[i]>data[i+1])
        {
            peak++;
            continue;
        }if(data[i]<data[i-1] && data[i]<data[i+1])
        {
            peak++;
            continue;
        }
    }
    return peak;
}
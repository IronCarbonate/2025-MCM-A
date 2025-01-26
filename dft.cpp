#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <valarray>
#include "read_data.hpp"

using namespace std;

double y_max=0;
double avg=0;

// 计算离散傅里叶变换（DFT）
vector<complex<double>> dft(const vector<double>& in) {
    int N = in.size();
    vector<complex<double>> X(N);
    for (int k = 0; k < N; ++k) {
        for (int n = 0; n < N; ++n) {
            double theta = -2 * M_PI * k * n / N;
            X[k] += in[n] * complex<double>(cos(theta), sin(theta));
        }
    }
    return X;
}

vector<complex<double>> dft_2(const vector<double>& in) {
    int N = in.size();
    vector<complex<double>> Y(N);
    for (int k = 0; k < N; ++k) {
        for (int n = 0; n < N; ++n) {
            double theta = -2 * M_PI * k * n / N;
            Y[k] += in[n] * complex<double>(cos(theta), sin(theta));
        }
    }
    return Y;
}

// 计算逆离散傅里叶变换（IDFT）
vector<double> idft(const vector<complex<double>>& in) {
    int N = in.size();
    vector<complex<double>> x(N);
    for (int n = 0; n < N; ++n) {
        for (int k = 0; k < N; ++k) {
            double theta = 2 * M_PI * k * n / N;
            x[n] += in[k] * complex<double>(cos(theta), sin(theta));
        }
        x[n] /= N;
    }
    vector<double> result(N);
    for (int i = 0; i < N; ++i) {
        if(i<=10)
            result[i] = 0;
        else
            result[i] = x[i].real();
    }
    return result;
}

// 归一化概率分布
void normalize(vector<double>& dist) {
    double sum = 0.0;
    for (double val : dist) {
        sum += val;
    }
    for (double& val : dist) {
        val /= sum;
    }
}

vector<double> GetGuass(vector<double>&x,double sigma)
{
    vector<double> result;
    for (int i = 0; i < x.size(); i++)
    {
        result.push_back(exp(-x[i] * x[i] / (2 * sigma * sigma)) / (sqrt(2 * M_PI) * sigma));
    }
    return result;
}

int main() {
    auto x = read_data("x_data.txt");
    auto y = read_data("y_data.txt");
    auto p = read_data("prop_data.txt");

    double sum=0;
    for(int i=0;i<y.size();i++)
    {
        if(y[i]>y_max)
            y_max=y[i];
        sum+=y[i];
    }
    avg=sum/y.size();

    // 示例数据：已知的卷积函数 h 和高斯分布 g 的离散点
    vector<double> h = y;
    vector<double> g = GetGuass(x, 0.1);

    // 计算傅里叶变换
    vector<complex<double>> H = dft(h);
    vector<complex<double>> G = dft(g);

    // 计算逆卷积
    vector<complex<double>> F(h.size());
    for (size_t i = 0; i < H.size(); ++i) {
        F[i] = H[i] / G[i]; // 注意：这里需要确保 G[i] 不为零
    }

    // 计算逆傅里叶变换
    vector<double> f = idft(F);

    // 归一化概率分布
    normalize(f);
    ofstream outFile("f.txt");
    if (!outFile.is_open()) {
        cerr << "无法打开文件 f.txt" << endl;
        return 1;
    }
    for (double val : f) {
        outFile << val << endl; // 每个值占一行
    }
    outFile.close();

    cout << "结果已写入 f.txt 文件" << endl;

    return 0;
}
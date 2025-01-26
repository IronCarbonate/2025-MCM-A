import numpy as np
import matplotlib
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

def probability_distribution(x, y, L):
    """
    定义概率分布函数。
    x: 位置数组
    y: 当前区域内的函数值
    L: 区域长度
    """
    base_prob = np.ones_like(x) * (0.5*np.exp(-((x - L / 2) ** 2) / (L ** 2 / 16))+0.5*np.exp(-((x - 3*L / 4) ** 2) / (L ** 2 / 16)))
    y_influence = y / 2*np.max(y) if np.max(y) > 0 else np.zeros_like(y)
    return base_prob * (1 + y_influence)

def add_gaussian(x, y, peak_position, amplitude, std_dev):
    """
    在给定的位置添加一个高斯函数。
    x: 位置数组
    y: 当前函数值
    peak_position: 高斯峰值位置
    amplitude: 高斯函数的峰值
    std_dev: 高斯函数的标准差
    """
    gaussian = amplitude * np.exp(-((x - peak_position) ** 2) / (2 * std_dev ** 2))
    return y + gaussian

def monte_carlo_simulation(L, N, num_iterations, amplitude, std_dev):
    """
    蒙特卡洛模拟主函数。
    L: 一维区域长度
    N: 离散点数量
    num_iterations: 模拟次数
    amplitude: 高斯峰值
    std_dev: 高斯标准差
    """
    x = np.linspace(0, L, N)
    y = np.zeros(N)

    for _ in range(num_iterations):
        prob_dist = probability_distribution(x, y, L)
        prob_dist /= np.sum(prob_dist)  # 归一化概率分布

        # 根据概率分布选择一个位置
        peak_position = np.random.choice(x, p=prob_dist)

        # 更新函数值
        y = add_gaussian(x, y, peak_position, amplitude, std_dev)

    return x, y

# 参数设置
L = 10  # 区域长度
N = 10000  # 离散点数量
num_iterations = 500  # 模拟次数
amplitude = 0.1  # 高斯峰值
std_dev = 0.5  # 高斯标准差

# 运行模拟
x, y = monte_carlo_simulation(L, N, num_iterations, amplitude, std_dev)
prob_dist = probability_distribution(x, y, L)
prob_dist /= np.sum(prob_dist)


np.savetxt("x_data.txt", x)
np.savetxt("y_data.txt", y)
np.savetxt("prop_data.txt", prob_dist)

# 绘制结果
plt.figure(figsize=(10, 6))
plt.plot(x, y, label="Monte Carlo Simulation")
plt.xlabel("Position")
plt.ylabel("Function Value")
plt.title("Monte Carlo Simulation of Gaussian Addition")
plt.legend()
plt.grid()
plt.show()

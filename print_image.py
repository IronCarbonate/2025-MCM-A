import numpy as np
import matplotlib.pyplot as plt

def plot_distribution(x_file, f_file, label):
    # 从文件中加载数据
    x = np.loadtxt(x_file)
    f = np.loadtxt(f_file)

    # 绘制图像
    plt.plot(x, f, marker='o', linestyle='-', label=label)

if __name__ == "__main__":
    # 指定文件路径
    x_file = "x_data.txt"
    y_file = "prop_data.txt"
    f_file = "f.txt"

    # 创建图像
    plt.figure(figsize=(10, 6))

    # 绘制两条曲线
    plot_distribution(x_file, y_file, 'p(x) Distribution')
    plot_distribution(x_file, f_file, 'f(x) Distribution')

    # 添加标题和标签
    plt.title('Distributions of p(x) and f(x)', fontsize=14)
    plt.xlabel('X', fontsize=12)
    plt.ylabel('Values', fontsize=12)
    plt.legend()
    plt.grid(True)

    # 显示图像
    plt.show()
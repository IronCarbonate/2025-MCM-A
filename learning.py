import numpy as np
import matplotlib.pyplot as plt
from skimage import io, color, filters
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestRegressor
from sklearn.metrics import mean_squared_error

# 假设我们有一些图像数据和对应的高斯分布参数
images = [...]  # 图像数据，形状为(n_samples, height, width)
params = [...]  # 高斯分布参数，形状为(n_samples, 2)，每行包含均值和方差

# 图像预处理和特征提取
def preprocess_and_extract_features(image):
    gray_image = color.rgb2gray(image)
    edges = filters.sobel(gray_image)
    return edges.flatten()

X = np.array([preprocess_and_extract_features(img) for img in images])
y = params

# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# 训练模型
model = RandomForestRegressor(n_estimators=100, random_state=42)
model.fit(X_train, y_train)

# 预测和评估
y_pred = model.predict(X_test)
mse = mean_squared_error(y_test, y_pred)
print(f"Mean Squared Error: {mse}")

# 可视化结果
plt.scatter(y_test[:, 0], y_pred[:, 0], label='Mean Prediction')
plt.scatter(y_test[:, 1], y_pred[:, 1], label='Variance Prediction')
plt.xlabel('True Values')
plt.ylabel('Predicted Values')
plt.legend()
plt.show()
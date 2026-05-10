#!/usr/bin/env python3
"""
Визуализация точек из файла points.txt
Использование: python3 visualize.py
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def visualize_points(filename="points.txt"):
    """Визуализирует точки из файла в 3D пространстве"""
    try:
        data = np.loadtxt(filename)
        if data.ndim == 1:
            data = data.reshape(1, -1)
        
        x, y, z = data[:, 0], data[:, 1], data[:, 2]
        
        fig = plt.figure(figsize=(10, 8))
        ax = fig.add_subplot(111, projection='3d')
        
        # Точки
        ax.scatter(x, y, z, c=z, cmap='viridis', s=5, alpha=0.7)
        
        # Сферы для визуализации границ
        u = np.linspace(0, 2 * np.pi, 50)
        v = np.linspace(0, np.pi, 50)
        
        # Здесь нужно было бы получить R1 и R2 из settings.dat
        # Для простоты - рисуем только точки
        
        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        ax.set_zlabel('Z')
        ax.set_title('Точки между сферами (визуализация)')
        
        plt.show()
        
    except FileNotFoundError:
        print("Файл points.txt не найден. Сначала сохраните точки из программы.")

if __name__ == "__main__":
    visualize_points()
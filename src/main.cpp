/**
 * @file main.cpp
 * @brief Тестовая программа для демонстрации работы генератора точек
 * @author Студент
 * @date 2026
 * 
 * @details Программа демонстрирует возможности класса SphereZoneGenerator:
 *          - Генерация массива случайных точек между сферами
 *          - Вывод координат произвольной точки
 *          - Добавление ручных точек
 *          - Сохранение точек в файл
 *          - Сохранение настроек области в файл
 */

#include "point3d.h"
#include "sphere_zone.h"
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>

/**
 * @brief Выводит главное меню программы
 */
void showMenu()
{
    std::cout << "\n========== МЕНЮ ==========\n";
    std::cout << "1 - Вывести координаты i-й точки\n";
    std::cout << "2 - Вывести отдельную координату i-й точки\n";
    std::cout << "3 - Добавить новую точку (ручной ввод)\n";
    std::cout << "4 - Сохранить все точки в файл points.txt\n";
    std::cout << "5 - Показать параметры области\n";
    std::cout << "6 - Сохранить параметры области в settings.dat\n";
    std::cout << "7 - Вывести ВСЕ точки на экран\n";
    std::cout << "0 - Выход\n";
    std::cout << "Ваш выбор: ";
}

/**
 * @brief Выводит координаты указанной точки из массива
 * @param points Вектор точек
 * @param index Индекс точки (1-based для пользователя)
 */
void printPoint(const std::vector<point3d>& points, int index)
{
    if (index >= 1 && index <= static_cast<int>(points.size())) {
        std::cout << "Точка №" << index << ": ";
        points[index - 1].print();
        std::cout << std::endl;
    } else {
        std::cout << "Ошибка: индекс должен быть от 1 до " << points.size() << std::endl;
    }
}

/**
 * @brief Выводит одну координату указанной точки
 * @param points Вектор точек
 * @param index Индекс точки (1-based)
 * @param coordChoice 1=x, 2=y, 3=z
 */
void printCoordinate(const std::vector<point3d>& points, int index, int coordChoice)
{
    if (index >= 1 && index <= static_cast<int>(points.size())) {
        const point3d& p = points[index - 1];
        std::cout << "Точка №" << index << ": ";
        switch(coordChoice) {
            case 1: std::cout << "X = " << p.getBackX(); break;
            case 2: std::cout << "Y = " << p.getBackY(); break;
            case 3: std::cout << "Z = " << p.getBackZ(); break;
            default: std::cout << "Неверный выбор координаты";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Ошибка: индекс должен быть от 1 до " << points.size() << std::endl;
    }
}

/**
 * @brief Добавляет точку с ручным вводом координат
 * @param points Вектор точек (модифицируется)
 */
void addManualPoint(std::vector<point3d>& points)
{
    double x, y, z;
    std::cout << "Введите координаты новой точки:\n";
    std::cout << "x = ";
    std::cin >> x;
    std::cout << "y = ";
    std::cin >> y;
    std::cout << "z = ";
    std::cin >> z;
    
    points.push_back(point3d(x, y, z));
    std::cout << "Точка успешно добавлена. Всего точек: " << points.size() << std::endl;
}

/**
 * @brief Сохраняет все точки в файл points.txt
 * @param points Вектор точек
 * @return true если успешно, false иначе
 */
bool savePointsToFile(const std::vector<point3d>& points)
{
    std::ofstream file("points.txt");
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл points.txt для записи\n";
        return false;
    }
    
    for (const auto& p : points) {
        file << p.getBackX() << "  " << p.getBackY() << "  " << p.getBackZ() << "\n";
    }
    
    file.close();
    std::cout << "Сохранено " << points.size() << " точек в файл points.txt\n";
    return true;
}

/**
 * @brief Выводит все точки на экран
 * @param points Вектор точек
 */
void printAllPoints(const std::vector<point3d>& points)
{
    std::cout << "\nВсе точки (" << points.size() << " шт.):\n";
    for (size_t i = 0; i < points.size(); ++i) {
        std::cout << "  [" << (i+1) << "] ";
        points[i].print();
        std::cout << std::endl;
    }
}

/**
 * @brief Главная функция программы
 * @return 0 при успешном завершении
 */
int main()
{
    std::cout << "========================================\n";
    std::cout << "   Генератор точек между сферами\n";
    std::cout << "========================================\n\n";
    
    // Ввод параметров области от пользователя
    double R1, R2;
    std::cout << "Введите параметры области (центр сфер - начало координат):\n";
    std::cout << "Внутренний радиус R1 (должен быть меньше R2): ";
    std::cin >> R1;
    std::cout << "Внешний радиус R2: ";
    std::cin >> R2;
    
    SphereZoneGenerator generator(R1, R2);
    generator.printSettings();
    
    // Ввод количества точек
    int K;
    std::cout << "\nВведите количество точек для генерации (1-10000): ";
    std::cin >> K;
    
    if (K < 1) K = 1;
    if (K > 10000) {
        std::cout << "K > 10000, ограничено до 10000.\n";
        K = 10000;
    }
    
    // Генерация массива точек
    std::vector<point3d> points;
    points.reserve(K);
    for (int i = 0; i < K; ++i) {
        points.push_back(generator.rnd());
    }
    std::cout << "Сгенерировано " << K << " случайных точек между сферами.\n";
    
    // Интерактивное меню
    int choice;
    do {
        showMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1: {
                int idx;
                std::cout << "Введите индекс точки (1-" << points.size() << "): ";
                std::cin >> idx;
                printPoint(points, idx);
                break;
            }
            case 2: {
                int idx, coord;
                std::cout << "Введите индекс точки (1-" << points.size() << "): ";
                std::cin >> idx;
                std::cout << "Какую координату вывести? (1-X, 2-Y, 3-Z): ";
                std::cin >> coord;
                printCoordinate(points, idx, coord);
                break;
            }
            case 3:
                addManualPoint(points);
                break;
            case 4:
                savePointsToFile(points);
                break;
            case 5:
                generator.printSettings();
                break;
            case 6:
                generator.saveSettingsToFile("settings.dat");
                break;
            case 7:
                printAllPoints(points);
                break;
            case 0:
                std::cout << "До свидания!\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
    
    return 0;
}
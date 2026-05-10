 /**
 * @file point3d.h
 * @brief Определение структуры для хранения трёхмерной точки
 * @author Студент
 * @date 2026
 */

#ifndef POINT3D_H
#define POINT3D_H

#include <iostream>

/**
 * @struct point3d
 * @brief Структура, представляющая точку в трёхмерном пространстве
 * 
 * @details Содержит координаты x, y, z и методы для доступа к ним и вывода.
 *          Все координаты имеют тип double. Центр системы координат находится
 *          в точке (0,0,0).
 */
struct point3d
{
    double x; ///< Координата X
    double y; ///< Координата Y
    double z; ///< Координата Z

    /**
     * @brief Конструктор по умолчанию
     * @param x Начальная координата X (по умолчанию 0.0)
     * @param y Начальная координата Y (по умолчанию 0.0)
     * @param z Начальная координата Z (по умолчанию 0.0)
     */
    point3d(double x = 0.0, double y = 0.0, double z = 0.0);

    /**
     * @brief Выводит координаты точки на экран
     * @details Формат вывода: (x, y, z)
     */
    void print() const;

    /**
     * @brief Возвращает координату X
     * @return Значение координаты X
     */
    double getBackX() const;

    /**
     * @brief Возвращает координату Y
     * @return Значение координаты Y
     */
    double getBackY() const;

    /**
     * @brief Возвращает координату Z
     * @return Значение координаты Z
     */
    double getBackZ() const;
};

#endif // POINT3D_H

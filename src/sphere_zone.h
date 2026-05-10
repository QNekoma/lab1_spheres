/**
 * @file sphere_zone.h
 * @brief Определение класса для генерации случайных точек между сферами
 * @author Студент
 * @date 2026
 */

#ifndef SPHERE_ZONE_H
#define SPHERE_ZONE_H

#include "point3d.h"
#include <random>
#include <iostream>
#include <fstream>
#include <string>

/**
 * @class SphereZoneGenerator
 * @brief Генератор случайных точек в области между двумя концентрическими сферами
 * 
 * @details Точки распределены равномерно по объёму между сферами радиуса R1 (внутренняя)
 *          и R2 (внешняя). Центр сфер находится в начале координат (0,0,0).
 *          Для генерации используется метод, основанный на равномерном распределении
 *          по объёму: сначала выбирается случайный радиус r в диапазоне [R1, R2]
 *          с кубическим распределением (плотность пропорциональна r^2),
 *          затем случайное направление (точка на единичной сфере).
 * 
 * @warning R1 должно быть меньше R2. При некорректных радиусах конструктор
 *          автоматически меняет их местами.
 */
class SphereZoneGenerator
{
private:
    double m_R1;                        ///< Внутренний радиус (малая сфера)
    double m_R2;                        ///< Внешний радиус (большая сфера)
    mutable std::mt19937 m_rng;         ///< Генератор случайных чисел Mersenne Twister
    mutable std::uniform_real_distribution<double> m_dist; ///< Равномерное распределение [0,1)

    /**
     * @brief Проверяет корректность радиусов и при необходимости исправляет
     * @details Если R1 > R2, значения меняются местами
     */
    void validateRadii();

public:
    /**
     * @brief Конструктор генератора
     * @param R1 Внутренний радиус (по умолчанию 1.0)
     * @param R2 Внешний радиус (по умолчанию 2.0)
     * @throws std::invalid_argument Если оба радиуса неположительные
     */
    SphereZoneGenerator(double R1 = 1.0, double R2 = 2.0);

    /**
     * @brief Генерирует одну случайную точку в заданной области
     * @return point3d Структура со случайными координатами
     * @details Точка гарантированно находится между сферами радиусов R1 и R2
     */
    point3d rnd() const;

    /**
     * @brief Выводит параметры области на экран
     * @details Формат: "R1 = значение, R2 = значение"
     */
    void printSettings() const;

    /**
     * @brief Записывает параметры области в файл
     * @param filename Имя файла для сохранения (по умолчанию "settings.dat")
     * @return true если запись успешна, false в противном случае
     */
    bool saveSettingsToFile(const std::string& filename = "settings.dat") const;

    /**
     * @brief Возвращает внутренний радиус
     * @return Значение R1
     */
    double getR1() const { return m_R1; }

    /**
     * @brief Возвращает внешний радиус
     * @return Значение R2
     */
    double getR2() const { return m_R2; }
};

#endif // SPHERE_ZONE_H 

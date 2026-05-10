/**
 * @file sphere_zone.cpp
 * @brief Реализация класса SphereZoneGenerator
 * @author Студент
 * @date 2026
 */

#include "sphere_zone.h"
#include <cmath>
#include <stdexcept>

void SphereZoneGenerator::validateRadii()
{
    if (m_R1 < 0 || m_R2 < 0) {
        throw std::invalid_argument("Радиусы не могут быть отрицательными");
    }
    if (m_R1 > m_R2) {
        std::swap(m_R1, m_R2);
        std::cout << "Предупреждение: R1 > R2, значения автоматически заменены.\n";
    }
    if (m_R1 == m_R2) {
        std::cout << "Предупреждение: R1 == R2, все точки будут на сфере.\n";
    }
}

SphereZoneGenerator::SphereZoneGenerator(double R1, double R2)
    : m_R1(R1), m_R2(R2), m_rng(std::random_device{}()), m_dist(0.0, 1.0)
{
    validateRadii();
}

point3d SphereZoneGenerator::rnd() const
{
    // Метод равномерного распределения точек по объёму между сферами:
    // 1. Генерируем радиус с плотностью r^2 в диапазоне [R1, R2]
    // 2. Генерируем случайное направление на единичной сфере
    
    // Шаг 1: Генерация радиуса
    // Для равномерного по объёму распределения радиус ~ r^2
    // Используем метод обратной функции: r = (R1^3 + u*(R2^3 - R1^3))^(1/3)
    double u = m_dist(m_rng);
    double r_cubed = m_R1 * m_R1 * m_R1 + u * (m_R2 * m_R2 * m_R2 - m_R1 * m_R1 * m_R1);
    double r = std::cbrt(r_cubed);
    
    // Шаг 2: Генерация случайного направления на единичной сфере
    // Используем метод Марсальи: нормальное распределение для x,y,z
    std::normal_distribution<double> norm_dist(0.0, 1.0);
    double nx = norm_dist(m_rng);
    double ny = norm_dist(m_rng);
    double nz = norm_dist(m_rng);
    
    // Нормализация вектора
    double norm = std::sqrt(nx * nx + ny * ny + nz * nz);
    nx /= norm;
    ny /= norm;
    nz /= norm;
    
    // Умножаем на случайный радиус
    return point3d(nx * r, ny * r, nz * r);
}

void SphereZoneGenerator::printSettings() const
{
    std::cout << "Параметры области генерации:\n";
    std::cout << "  Внутренний радиус R1 = " << m_R1 << "\n";
    std::cout << "  Внешний радиус R2 = " << m_R2 << "\n";
    std::cout << "  Область: между концентрическими сферами\n";
}

bool SphereZoneGenerator::saveSettingsToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << " для записи\n";
        return false;
    }
    
    file << "# Настройки генератора точек между сферами\n";
    file << "# Формат: R1 R2\n";
    file << m_R1 << " " << m_R2 << "\n";
    
    file.close();
    std::cout << "Настройки сохранены в файл " << filename << "\n";
    return true;
}
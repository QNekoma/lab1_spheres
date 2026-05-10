/**
 * @file sphere_zone.cpp
 * @brief Реализация класса SphereZoneGenerator
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
    }
}

SphereZoneGenerator::SphereZoneGenerator(double R1, double R2)
    : m_R1(R1), m_R2(R2), m_rng(std::random_device{}()), m_dist(0.0, 1.0)
{
    validateRadii();
}

point3d SphereZoneGenerator::rnd() const
{
    double u = m_dist(m_rng);
    double r_cubed = m_R1 * m_R1 * m_R1 + u * (m_R2 * m_R2 * m_R2 - m_R1 * m_R1 * m_R1);
    double r = std::cbrt(r_cubed);
    
    std::normal_distribution<double> norm_dist(0.0, 1.0);
    double nx = norm_dist(m_rng);
    double ny = norm_dist(m_rng);
    double nz = norm_dist(m_rng);
    
    double norm = std::sqrt(nx * nx + ny * ny + nz * nz);
    
    return point3d(nx * r / norm, ny * r / norm, nz * r / norm);
}

void SphereZoneGenerator::printSettings() const
{
    std::cout << "Параметры области генерации:\n";
    std::cout << "  R1 = " << m_R1 << ", R2 = " << m_R2 << std::endl;
}

bool SphereZoneGenerator::saveSettingsToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    file << m_R1 << " " << m_R2 << std::endl;
    file.close();
    return true;
}
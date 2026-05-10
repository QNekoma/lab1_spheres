/**
 * @file sphere_zone.h
 * @brief Определение класса для генерации случайных точек между сферами
 */

#ifndef SPHERE_ZONE_H
#define SPHERE_ZONE_H

#include "point3d.h"
#include <random>
#include <iostream>
#include <fstream>
#include <string>

class SphereZoneGenerator
{
private:
    double m_R1, m_R2;
    mutable std::mt19937 m_rng;
    mutable std::uniform_real_distribution<double> m_dist;

    void validateRadii();

public:
    SphereZoneGenerator(double R1 = 1.0, double R2 = 2.0);
    point3d rnd() const;
    void printSettings() const;
    bool saveSettingsToFile(const std::string& filename = "settings.dat") const;
    double getR1() const { return m_R1; }
    double getR2() const { return m_R2; }
};

#endif // SPHERE_ZONE_H
 /**
 * @file point3d.cpp
 * @brief Реализация методов структуры point3d
 * @author Студент
 * @date 2026
 */

#include "point3d.h"

point3d::point3d(double x, double y, double z)
    : x(x), y(y), z(z)
{
}

void point3d::print() const
{
    std::cout << "(" << x << ", " << y << ", " << z << ")";
}

double point3d::getBackX() const
{
    return x;
}

double point3d::getBackY() const
{
    return y;
}

double point3d::getBackZ() const
{
    return z;
}

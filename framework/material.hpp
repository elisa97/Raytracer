#ifndef MATERIAL_HPP
#define MATERIAL_HPP

// header, system
#include <iostream>
#include <string>

// header, project
#include "color.hpp"

struct  Material
{
    std::string name = "def material";
    Color ka{0.0f,0.0f,0.0f};
    Color kd{0.0f,0.0f,0.0f};
    Color ks{0.0f,0.0f,0.0f};
    float m = 1.0f;
    float opacity = 0.0f;

    Material(){}
    Material(std::string name_c, Color ka_c, Color kd_c, Color ks_c, float m_c)
    {
        name = name_c;
        ka = ka_c;
        kd = kd_c;
        ks = ks_c;
        m = m_c;
    }
    std::ostream& print(std::ostream& os);
};

std::ostream& operator<<(std::ostream& os, Material& material);

bool operator ==(Material const& lhs, Material const& rhs);

#endif
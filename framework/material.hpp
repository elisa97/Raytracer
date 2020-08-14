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
    Color ka{0,0,0};
    Color kd{0,0,0};
    Color ks{0,0,0};
    float m = 1.0f;

    Material(){}
    Material(std::string name_c, Color ka_c, Color kd_c, Color ks_c, float m)
    {
        name = name_c;
        ka = ka_c;
        kd = kd_c;
        ks = ks_c;
        m = m;
    }
    std::ostream& print(std::ostream& os);
};

std::ostream& operator<<(std::ostream& os, Material& material);

bool operator ==(Material const& lhs, Material const& rhs);

#endif
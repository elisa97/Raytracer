#ifndef MATERIAL_HPP
#define MATERIAL_HPP

// header, system
#include <iostream>
#include <string>

// header, project
#include "color.hpp"

struct  Material
{
    std::string name_ = "standard rough";
    Color ka_{0,0,0};
    Color kd_{0,0,0};
    Color ks_{0,0,0};
    float m_ = 1;

    Material(){}
    Material(std::string name, Color ka, Color kd, Color ks, float m)
    {
        name_ = name;
        ka_ = ka;
        kd_ = kd;
        ks_ = ks;
        m_ = m;
    }
    std::ostream& print(std::ostream& os);
};

std::ostream& operator<<(std::ostream& os, Material& material);

bool operator ==(Material const& lhs, Material const& rhs);

#endif
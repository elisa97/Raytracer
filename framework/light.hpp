#ifndef LIGHT_HPP
#define LIGHT_HPP

// header, external
#include <glm/vec3.hpp>

// header, project
#include "color.hpp"

struct Light
{
    std::string name = "light0";
    float brightness = 1.0f;
    Color lcol = {0.5f, 0.5f, 0.5f};
    glm::vec3 lloc = {10.0f, 0.0f, 0.0f};
};

#endif
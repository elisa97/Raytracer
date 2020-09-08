#ifndef LIGHT_HPP
#define LIGHT_HPP

// header, external
#include <glm/vec3.hpp>

// header, project
#include "color.hpp"

struct Light
{
    std::string name = "default";
    float brightness = 0.5f;
    Color color = {0.5f, 0.5f, 0.5f};
    glm::vec3 location = {0.0f, 0.0f, 0.0f};
    //to long line
    Color intensity = {color.r * brightness, color.g * brightness, color.b * brightness}; //no bound check yet 
};

#endif
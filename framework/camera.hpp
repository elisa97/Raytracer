#ifndef CAMERA_HPP
#define CAMERA_HPP

// header, external
#include <glm/vec3.hpp>

// header, system
#include <string>
#include <fstream>
#include <sstream>

//header, project
#include "ray.hpp"

struct Camera {

    std::string name = "";
    float fov_x = 60.0;  // between 0 and 180
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    glm::vec3 direction = {0.0f, 0.0f, -1.0f};
    glm::vec3 up = {0.0f, 1.0f, 0.0f};
};

#endif
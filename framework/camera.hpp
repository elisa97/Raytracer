#ifndef CAMERA_HPP
#define CAMERA_HPP

// External libraries
#include <glm/vec3.hpp>

// Standard libraries
#include <string>
#include <fstream>
#include <sstream>


struct Camera {

    std::string name = "";
    float fov_x = 60.0;  // between 0 and 180
    glm::vec3 position = {0.0f, 0.0f, 0.0f};
    glm::vec3 direction = {0.0f, 0.0f, -1.0f};

    //Ray shoot_ray () Methode implementieren?
};

#endif
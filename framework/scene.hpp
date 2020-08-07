#ifndef SCENE_HPP
#define SCENE_HPP

#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <algorithm>
#include <glm/vec3.hpp>
#include "Material.hpp"
#include "Sphere.hpp"
#include "Box.hpp"

struct Scene
{
    std::string name = "default_name";
    std::map<std::string, std::shared_ptr<Material>> materials{};
    std::vector<std::shared_ptr<Shape>> objects{};
    std::vector<Light> lights{};
    Color ambient{0.0f, 0.0f, 0.0f};
    std::vector<std::string, Camera> cameras{};

    Camera camera;
    Color ambient {1.0f,1.0f,1.0f};
     
}

#endif
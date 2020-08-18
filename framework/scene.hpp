#ifndef SCENE_HPP
#define SCENE_HPP

// header, external
#include <glm/vec3.hpp>

// header, system
#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <algorithm>

// header, project
#include "material.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "camera.hpp"
#include "light.hpp"

struct Scene
{
    std::string name = "default_name";
    std::map<std::string, std::shared_ptr<Material>> materials{};
    std::vector<std::shared_ptr<Shape>> objects{};
    std::vector<Light> lights{};
    Camera camera;
    Color background {0.0f, 0.0f, 0.0f};
    Color ambient {1.0f, 1.0f, 1.0f};
};

Scene importScene(std::string const& path);

#endif
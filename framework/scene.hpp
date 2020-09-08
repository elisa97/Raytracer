#ifndef SCENE_HPP
#define SCENE_HPP

// header, project
#include "material.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "triangle.hpp"

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



struct Scene
{
    std::map<std::string, std::shared_ptr<Material>> materials{};
    std::vector<std::shared_ptr<Shape>> objects{};
    std::vector<Light> lights{};
    std::string name = "default";
    Camera      camera;
    Color       background {};
    Light       ambient {};
};

Scene importScene(std::string const& path, bool verbose);

#endif
#ifndef HITPOINT_HPP
#define HITPOINT_HPP

// header, project
#include "material.hpp"

//header, external
#include <glm/vec3.hpp>

struct HitPoint
{
  bool                      cut = false;  
  float                     cdist = -1.0f;
  std::string               name = "default";
  std::shared_ptr<Material> material{};
  glm::vec3                 hit{};
  glm::vec3                 normal{};
  glm::vec3                 direction{};
};

#endif
#ifndef HITPOINT_HPP
#define HITPOINT_HPP

//header, external
#include <glm/vec3.hpp>

// header, project
#include "material.hpp"

struct HitPoint
{
  bool cut = false;                      //1
  float cdist = -1.0f;                   //2
  std::string name = "default";          //3
  std::shared_ptr<Material> material{};  //4
  glm::vec3 origin{};                    //5 (direction)
  glm::vec3 normal{};                    //6
  glm::vec3 hit{};                       //7
};

#endif
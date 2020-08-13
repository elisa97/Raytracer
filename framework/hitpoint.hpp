#ifndef HITPOINT_HPP
#define HITPOINT_HPP

// header, project
#include "material.hpp"
#include "ray.hpp"

struct HitPoint
{
  bool cut = false;            //1
  float cdist = -1.0f;         //2
  std::string name = "default";  //3
  Material mat = {};              //4
  Ray pt_dir = {};             //5+6
};

#endif
#ifndef RAY_HPP
#define RAY_HPP

// header, external
#include <glm/glm.hpp>

struct Ray
{
  glm::vec3 origin = {0.0f, 0.0f, 0.0f};
  glm::vec3 direction = {0.0f, 0.0f, -1.0f};

  Ray transformRay(Ray const& ray, glm::mat4 const& mat);
};


#endif
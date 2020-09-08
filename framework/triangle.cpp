#include "triangle.hpp"

Triangle::Triangle():
  a_ {}, 
  b_ {},
  c_ {} {}
Triangle::Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c):
  a_ {a},
  b_ {b},
  c_ {c} {}

Triangle::Triangle(glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c,
                   std::string const& name, std::shared_ptr<Material> material):
  a_ {a},
  b_ {b},
  c_ {c}
{
  name_ = name;
  material_ = material;
}

float Triangle::area() const 
{
  return glm::length(glm::cross(b_ - a_, c_ - a_) / 2.0f);
}

float Triangle::volume() const
{
  return 0;
}

HitPoint Triangle::intersect(Ray const& ray) const 
{
  Ray trans_ray = transform_ray(ray, world_transformation_inv_);
  trans_ray.direction = glm::normalize(trans_ray.direction);
  glm::vec3 pos;
  HitPoint hp;
  float d = 0.0f;
  hp.cut = glm::intersectRayTriangle(trans_ray.origin, trans_ray.direction, a_, b_, c_, pos);

  if (hp.cut) {
    glm::vec3 trans_vec = trans_ray.direction - trans_ray.origin;
    glm::vec3 vec (trans_vec / glm::length(trans_vec));

    //hp.cdist = glm::distance(trans_ray.origin, pos);
    hp.cdist = d;
    hp.name = name_;
    hp.material = material_;
    hp.direction = trans_ray.direction;
    hp.hit = vec * hp.cdist;
    hp.normal = glm::cross(b_ - a_, c_ - a_);
    return hp;
  }
  
  return{};
}
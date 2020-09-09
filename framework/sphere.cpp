#include "sphere.hpp"

Sphere::Sphere():
  mid_ {},
  rad_ {10.0f} {}

Sphere::~Sphere() {}

Sphere::Sphere(glm::vec3 const& m , float r):
  mid_ {m},
  rad_ {abs(r)} {}

Sphere::Sphere(glm::vec3 const& m , float r, std::string const& name, std::shared_ptr<Material> material):
  mid_{m},
  rad_{abs(r)} 
{
  name_ = name;
  material_ = material;
}

float Sphere::area() const
{
  return (4.0f * M_PI * pow(rad_, 2.0f));
}

float Sphere::volume() const 
{
  return (4.0f / 3.0f * M_PI * pow(rad_, 3.0f));
}

std::ostream& Sphere::print(std::ostream & os) const 
{
   return os 
   << "Sphere "   << name_           << "\n"
   << "Material " << material_->name << "\n"
   << "Middle ("  << mid_.x
   << ", "        << mid_.y
   << ", "        << mid_.z 
   << ") \n Radian " << rad_         << "\n";
}

HitPoint Sphere::intersect(Ray const& r) const 
{
  Ray trans_ray = transform_ray(r, world_transformation_inv_);
  glm::vec3 pos, n;
  bool result = glm::intersectRaySphere(trans_ray.origin, 
                                        glm::normalize(trans_ray.direction),
                                        mid_, rad_ , pos, n);

  if (result) {
    // glm::vec4 trans_n;
    // trans_n = glm::normalize(glm::transpose(world_transformation_inv_)
    //                          * glm::vec4(n, 0));
    // glm::vec4 trans_hp = world_transformation_ * glm::vec4(pos, 1);
    // n = {trans_n.x, trans_n.y, trans_n.z};
    // pos = {trans_hp.x, trans_hp.y, trans_hp.z};
    float d = glm::distance(trans_ray.origin, pos);
    HitPoint hp {true, d, name_, material_, pos, n, trans_ray.direction};
    rev_trans(hp, world_transformation_, glm::transpose(world_transformation_inv_));
    return hp;
  }
  
  return{};
}
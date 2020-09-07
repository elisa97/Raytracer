#include "sphere.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include <cmath>

Sphere::Sphere() {
  mid_ = {0.0f, 0.0f, 0.0f};
  rad_ = 10.0f;
  name_ = "default";
  std::shared_ptr<Material> mat1(new Material{});
  material_ = mat1;
}

Sphere::~Sphere() {
  //std::cout << "Dstr/Sphere " << name_ << "\n";
}

Sphere::Sphere(glm::vec3 const& m , float r)  {
  mid_ = m;
  rad_ = abs(r);
  name_ = "default";
  std::shared_ptr<Material> mat1(new Material{});
  material_ = mat1;
}

Sphere::Sphere(glm::vec3 const& m , float r, std::string const& name, std::shared_ptr<Material> material)  {
 // std::cout << "Cnst/Sphere " << name_ << "\n";
  mid_ = m;
  rad_ = abs(r);
  name_ = name;
  material_ = material;
}

float Sphere::area() const {
  return (4.0f * M_PI * pow(rad_, 2.0f));
}

float Sphere::volume() const {
  return (4.0f / 3.0f * M_PI * pow(rad_, 3.0f));
}

std::ostream& Sphere::print(std::ostream & os) const {
   return os << "Sphere " << name_ << "\nMaterial name: " 
   << material_->name << "\nMiddle: (" << mid_.x << "|" 
   << mid_.y << "|" << mid_.z << ") Radian: " << rad_ << "\n\n";
}

HitPoint Sphere::intersect(Ray const& r) const {
  Ray transRay_ = transformRay(r, world_transformation_inv_);
  glm::vec3 pos, n;
  bool res = glm::intersectRaySphere(transRay_.origin, glm::normalize(transRay_.direction), mid_, rad_ , pos, n);

  if (res) {
    float d = glm::distance(transRay_.origin, pos);
    return{true, d, name_, material_, pos, n, transRay_.direction};
  }
  
  return{};
}
#include "sphere.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include <cmath>

Sphere::Sphere():
  mid_{},
  rad_{10.0f} {
}

Sphere::~Sphere() {
  //std::cout << "Dstr/Sphere " << name_ << "\n";
}

Sphere::Sphere(glm::vec3 const& m , float r):
  mid_{m},
  rad_{abs(r)} {
}

Sphere::Sphere(glm::vec3 const& m , float r, std::string const& name, std::shared_ptr<Material> material):
  mid_{m},
  rad_{abs(r)} {
    name_ = name;
    material_ = material;
}

float Sphere::area() const {
  return (4.0f * M_PI * pow(rad_, 2.0f));
}

float Sphere::volume() const {
  return (4.0f / 3.0f * M_PI * pow(rad_, 3.0f));
}

std::vector<glm::vec3> Sphere::mv_mid() {
  std::vector<glm::vec3> point;
  auto mid_old = mid_;
  point.push_back(mid_old);
  mid_ = {0.0f, 0.0f, 0.0f};
  return point;
}

void Sphere::mv_back(std::vector<glm::vec3> const& v) {
  mid_ = v[0];
}

std::ostream& Sphere::print(std::ostream & os) const {
   return os << "Sphere " << name_ << "\nMaterial name: " 
   << material_->name << "\nMiddle: (" << mid_.x << "|" 
   << mid_.y << "|" << mid_.z << ") Radian: " << rad_ << "\n\n";
}

HitPoint Sphere::intersect(Ray const& r) const {
  Ray transRay_ = transform_ray(r, world_transformation_inv_);
  glm::vec3 pos, n;
  bool res = glm::intersectRaySphere(transRay_.origin, glm::normalize(transRay_.direction), mid_, rad_ , pos, n);

  if (res) {
    glm::vec4 trans_n = glm::normalize(glm::transpose(world_transformation_inv_) * glm::vec4(n,0));
    glm::vec4 trans_hp = world_transformation_ * glm::vec4(pos,1);
    n = {trans_n.x, trans_n.y, trans_n.z};
    pos = {trans_hp.x, trans_hp.y, trans_hp.z};
    float d = glm::distance(transRay_.origin, pos);
    HitPoint hit{true, d, name_, material_, pos, n, transRay_.direction};
    //rev_trans(hit, world_transformation_, glm::transpose(world_transformation_inv_));
    return hit;
  }
  
  return{};
}
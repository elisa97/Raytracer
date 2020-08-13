#include "box.hpp"

#include "cmath"

Box::Box() {
  topr_ = {5, 5, 5};
  botl_ = {-5, -5, -5};
  name_ = "default";
  material_ = {};
}

Box::Box(glm::vec3 const& lhs, glm::vec3 const& rhs) {
  topr_ = lhs;
  botl_ = rhs;
  name_ = "Phteven";
  material_ = {};
}

Box::Box(glm::vec3 const& lhs, glm::vec3 const& rhs, 
        std::string const& n, std::shared_ptr<Material> mat) {
  topr_ = lhs;
  botl_ = rhs;
  name_ = n;
  material_ = mat;
}

float Box::area() const {
  glm::vec3 tmp = topr_ - botl_;
  float res = abs(2 * tmp.x * tmp.y);
  res = res + abs(2 * tmp.y * tmp.z);
  res = res + abs(2 * tmp.x * tmp.z);
  return res;
}

float Box::volume() const {
  glm::vec3 tmp = topr_ - botl_;
  return abs(tmp.x * tmp.y * tmp.z);
}

std::ostream& Box::print(std::ostream & os) const {
   return os << "Box " << name_ << "\n Material: " << material_->name 
   << "\nPoints: (" << topr_.x << "|" << topr_.y << "|" << topr_.z 
   << ") (" << botl_.x << "|" << botl_.y << "|" << botl_.z << ")\n\n";
}

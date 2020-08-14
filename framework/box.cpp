#include "box.hpp"

Box::Box() {
  min_ = {0.0f, 0.0f, 0.0f};
  max_ = {0.0f, 0.0f, 0.0f};
  name_ = "default";
  std::shared_ptr<Material> mat1(new Material{});
  material_ = mat1;
}

/*Box::Box():
    Shape(),
    min_ {(0.0f, 0.0f, 0.0f)},
    max_ {(0.0f, 0.0f, 0.0f)}{}
*/
Box::Box(glm::vec3 const& lhs, glm::vec3 const& rhs) {
  min_ = lhs;
  max_ = rhs;
  name_ = "default";
  std::shared_ptr<Material> mat1(new Material{});
  material_ = mat1;
}

Box::Box(glm::vec3 const& lhs, glm::vec3 const& rhs, 
        std::string const& name, std::shared_ptr<Material> material) {
  min_ = lhs;
  max_ = rhs;
  name_ = name;
  material_ = material;
}

float Box::area() const {
  glm::vec3 tmp = max_ - min_;
  float res = abs(2 * tmp.x * tmp.y);
  res = res + abs(2 * tmp.y * tmp.z);
  res = res + abs(2 * tmp.x * tmp.z);
  return res;
}

float Box::volume() const {
  glm::vec3 tmp = max_ - min_;
  return abs(tmp.x * tmp.y * tmp.z);
}

std::ostream& Box::print(std::ostream & os) const {
   return os << "Box " << name_ << "\nMaterial: " << material_->name 
   << "\nPoints: (" << max_.x << "|" << max_.y << "|" << max_.z 
   << ") (" << min_.x << "|" << min_.y << "|" << min_.z << ")\n\n";
}

HitPoint Box::intersect(Ray const& ray) const {
    HitPoint hitpoint{};
   bool hit;
   float t_min = MAXFLOAT;

   //back
   float t = (min_.x - ray.origin.x) / (glm::normalize(ray.direction)).x;
   glm::vec3 px = ray.origin + t * (glm::normalize(ray.direction));
   if (px.y <= max_.y && px.y >= min_.y && px.z <= max_.z && px.z >= min_.z && t > 0) {
     hit = true;
     t_min = t;
     hitpoint.origin= px;
     hitpoint.normal = glm::vec3{-1.0f, 0.0f, 0.0f};
   }
}

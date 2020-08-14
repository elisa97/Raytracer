#include "box.hpp"

Box::Box() {
  min_ = {0.0f, 0.0f, 0.0f};
  max_ = {0.0f, 0.0f, 0.0f};
  name_ = "default";
  std::shared_ptr<Material> mat1(new Material{});
  material_ = mat1;
}

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
    float t = (min_.x - ray.origin.x) / ray.direction.x;
    glm::vec3 p = ray.origin + t * ray.direction;

    if (p.y > min_.y && p.y < max_.y && p.z > min_.z && p.z < max_.z){
        hitpoint.cut = true;
        hitpoint.cdist = t;
        hitpoint.name = name_;
        hitpoint.material = material_;
        hitpoint.pt_dir.origin = ray.origin + t * ray.direction;
        hitpoint.pt_dir.direction = ray.direction;
        //auto ct = ray.origin + t * ray.direction;
        //auto n = ray.direction;
        //hitpoint.pt_dir = {ct, n};
        return hitpoint;
    }
    else{
        hitpoint.cut = false;
        return hitpoint;
    }
}

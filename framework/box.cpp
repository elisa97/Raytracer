#include "box.hpp"

Box::Box():
  min_ {},
  max_ {} {}

Box::Box(glm::vec3 const& lhs, glm::vec3 const& rhs):
  min_ {lhs},
  max_ {rhs} 
{
  min_max();
}

Box::Box(glm::vec3 const& lhs, glm::vec3 const& rhs, 
        std::string const& name, std::shared_ptr<Material> material):
  min_ {lhs},
  max_ {rhs}
{
  min_max();
  name_ = name;
  material_ = material;
}

float Box::area() const 
{
  glm::vec3 tmp = max_ - min_;
  float res = abs(2 * tmp.x * tmp.y);
  res = res + abs(2 * tmp.y * tmp.z);
  res = res + abs(2 * tmp.x * tmp.z);
  return res;
}

float Box::volume() const 
{
  glm::vec3 tmp = max_ - min_;
  return abs(tmp.x * tmp.y * tmp.z);
}

std::vector<glm::vec3> Box::mv_mid() 
{
  std::vector<glm::vec3> points;
  points.push_back(min_);
  points.push_back(max_);
  glm::vec3 vec2mid = (max_ - min_) / 2.0f;
  max_ = vec2mid;
  min_ = -vec2mid;
  return points;
}

void Box::mv_back(std::vector<glm::vec3> const& v) 
{
  min_ = v[0];
  max_ = v[1];
}

//function to correctly set the values for min and max
void Box::min_max() 
{
  for (int i = 0; i < 3; ++i) {
    if (min_[i] > max_[i]) {
      std::swap(min_[i], max_[i]);
    }
  }
}

std::ostream& Box::print(std::ostream & os) const 
{
   return os
   << "Box "       << name_           << "\n"
   << "Material: " << material_->name << "\n"
   << "Points: ("  << min_.x 
   << "|"          << min_.y 
   << "|"          << min_.z          << "\n"
   << ") ("        << max_.x 
   << "|"          << max_.y 
   << "|"          << max_.z          << ")\n";
}

void Box::intersect_plane(HitPoint& hitpoint, Ray const& ray, 
                          int dim, bool side, float plane_value) const
{
  glm::vec3 n = glm::normalize(ray.direction);
  float t = (plane_value - ray.origin[dim]) / n[dim];
  glm::vec3 plane_point = ray.origin + (t * n);

  if  ((plane_point[(dim+1)%3] >= min_[(dim+1)%3]) 
    && (plane_point[(dim+1)%3] <= max_[(dim+1)%3])
    && (plane_point[(dim+2)%3] >= min_[(dim+2)%3]) 
    && (plane_point[(dim+2)%3] <= max_[(dim+2)%3])) {
      
      glm::vec3 normal{};
      normal[dim] = (side) ? -1 : 1;
      hitpoint.cut = true;
      hitpoint.cdist = t;
      hitpoint.name = name_;
      hitpoint.material = material_;
      hitpoint.direction = n;
      hitpoint.normal = normal;
      hitpoint.hit = plane_point;
    }
}

HitPoint Box::intersect(Ray const& ray) const 
{
  HitPoint result{};
  float epsilon= -0.0001f;
  for (int side = 0; side < 2; side++) {
    for (int dim = 0; dim < 3; dim++) {
      HitPoint hp{};
      Ray transform = transform_ray(ray, world_transformation_inv_);
      if (side == 0) {
        this->intersect_plane(hp, transform, dim, true, min_[dim]+ epsilon);
      } else {
        this->intersect_plane(hp, transform, dim, false, max_[dim]- epsilon);
      }
      
      if (hp.cut) {
        if (!result.cut || hp.cdist < result.cdist) {
          result = hp;
        }
      }
      rev_trans(hp, world_transformation_, 
                glm::transpose(world_transformation_inv_));
    }
  }
  return result;
}


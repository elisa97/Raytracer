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

// function to correctly set the values for min and max
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
  << "Box name: " << name_           << "\n"
  << "material: " << material_->name << "\n"
  << "min: ("     << min_.x 
  << ", "         << min_.y 
  << ", "         << min_.z          << ")\n"
  << "max: ("     << max_.x 
  << ", "         << max_.y 
  << ", "         << max_.z          << ")\n";
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
  Ray transform = transform_ray(ray, world_transformation_inv_);
  float epsilon= -0.0001f;
  for (int side = 0; side < 2; side++) {
    for (int dim = 0; dim < 3; dim++) {
      HitPoint hp{};

      if (side == 0) {
        intersect_plane(hp, transform, dim, true, min_[dim]+ epsilon);
      } else {
        intersect_plane(hp, transform, dim, false, max_[dim]- epsilon);
      }
      
      if (hp.cut) {
        if (!result.cut || hp.cdist < result.cdist) {
          result = hp;
        }
      }
    }
  }
  rev_trans(result, world_transformation_, 
            glm::transpose(world_transformation_inv_));
  return result;
}


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

   //front
   float t_max_x = (max_.x - ray.origin.x) / (glm::normalize(ray.direction)).x;
   glm::vec3 px2 = ray.origin + t_max_x * (glm::normalize(ray.direction));
   if (px2.y <= max_.y && px2.y >= min_.y && px2.z <= max_.z && px2.z >= min_.z && t_max_x > 0) {
     hit = true;
     if (t_min > t_max_x) {
       hitpoint.origin = px2;
       t_min = t_max_x;
       hitpoint.normal = glm::vec3{1.0f, 0.0f, 0.0f};
     }
   }

   //down
   float t_min_y = (min_.y - ray.origin.y) / (glm::normalize(ray.direction)).y;
   glm::vec3 py = ray.origin + t_min_y * (glm::normalize(ray.direction));
   if (py.x <= max_.x && py.x >= min_.x && py.z <= max_.z && py.z >= min_.z && t_min_y > 0) {
     hit = true;
     if (t_min > t_min_y) {
       hitpoint.origin = py;
       t_min = t_min_y;
       hitpoint.normal = glm::vec3{0.0f, -1.0f, 0.0f};
     }
   }

   //up
   float t_max_y = (max_.y - ray.origin.y) / (glm::normalize(ray.direction)).y;
   glm::vec3 py2 = ray.origin + t_max_y * (glm::normalize(ray.direction));
   if (py2.x <= max_.x && py2.x >= min_.x && py2.z <= max_.z && py2.z >= min_.z && t_max_y > 0) {
     hit = true;
     if (t_min > t_max_y) {
       hitpoint.origin = py2;
       t_min = t_max_y;
       hitpoint.normal = glm::vec3{0.0f, 1.0f, 0.0f};
     }
   }

   //right
   float t_min_z = (min_.z - ray.origin.z) / (glm::normalize(ray.direction)).z;
   glm::vec3 pz = ray.origin + t_min_z * (glm::normalize(ray.direction));
   if (pz.x <= max_.x && pz.x >= min_.x && pz.y <= max_.y && pz.y >= min_.y && t_min_z > 0) {
     hit = true;
     if (t_min > t_min_z) {
       hitpoint.origin = pz;
       t_min = t_min_z;
       hitpoint.normal = glm::vec3{0.0f, 0.0f, -1.0f};
     }
   }
  
  //left
  float t_max_z = (max_.z - ray.origin.z) / (glm::normalize(ray.direction)).z;
   glm::vec3 pz2 = ray.origin + t_max_z * (glm::normalize(ray.direction));
   if (pz2.x <= max_.x && pz2.x >= min_.x && pz2.y <= max_.y && pz2.y >= min_.y && t_max_z > 0) {
     hit = true;
     if (t_min > t_max_z) {
       hitpoint.origin = pz2;
       t_min = t_max_z;
       hitpoint.normal = glm::vec3{0.0f, 0.0f, 1.0f};
     }
   }
   if (hit) {
     hitpoint.cut = true;
     hitpoint.material = material_;
     hitpoint.origin = ray.direction;
     hitpoint.cdist = t_min;
     hitpoint.name = name_;
   }
   return hitpoint;
}

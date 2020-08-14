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
  //float t = (min_.x - ray.origin.x) / ray.direction.x;
  //glm::vec3 p = ray.origin + t * ray.direction;
  //float t = (min_.x - ray.origin.x) / ray.direction.x;
  //glm::vec3 p = ray.origin + t * ray.direction;

  float t_x_min = (min_.x - ray.origin.x) / ray.direction.x;
  float t_x_max = (max_.x - ray.origin.x) / ray.direction.x;
  float t_y_min = (min_.y - ray.origin.y) / ray.direction.y;
  float t_y_max = (max_.y - ray.origin.y) / ray.direction.y;
  float t_near = -1000000.0f;
  float t_far = 1000000.0f;

  //if (p.y > min_.y && p.y < max_.y && p.z > min_.z && p.z < max_.z){

  if (t_x_min > t_y_max || t_y_min > t_x_max){
    return hitpoint;
  }
  else{
    hitpoint.cut = true;
    float t = 40.0f;
    hitpoint.cdist = t;
    hitpoint.name = name_;
    hitpoint.material = material_;
    hitpoint.origin = ray.origin + t * ray.direction;
    hitpoint.normal = ray.direction;
    return hitpoint;
  }
/*HitPoint hitpoint{};
HitPoint temp_hitpoint{};
glm::vec3 direction = glm::normalize(ray.direction);

//back
if (direction.x != 0){
  float t = (-ray.origin.x + max_.x) / direction.x;
  float x = ray.origin.x + t * direction.x;
  float y = ray.origin.y + t * direction.y;
  float z = ray.origin.z + t * direction.z;

  if (y > min_.y && y < max_.y && z > min_.z && z < max_.z){
    float distance = sqrt(pow(ray.origin.x - x, 2)+ pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
    HitPoint new_hit{true, distance, name_, material_, glm::vec3(x, y, z), direction};
    temp_hitpoint = new_hit;
    if (hitpoint.cdist >= 0 && temp_hitpoint.cdist >= 0 && temp_hitpoint.cdist < hitpoint.cdist){
      hitpoint = temp_hitpoint;
    }
  }
}
/*float t = (min_.x - ray.origin.x) / (glm::normalize(ray.direction)).x;
glm::vec3 px = ray.origin + t * (glm::normalize(ray.direction));
if (px.y <= max_.y && px.y >= min_.y && px.z <= max_.z && px.z >= min_.z && t > 0) {
  hit = true;
  t_min = t;
  hitpoint.origin= px;
  hitpoint.normal = glm::vec3{-1.0f, 0.0f, 0.0f};


  //front
  if (direction.x != 0){
    float t = (-ray.origin.x + min_.x) / direction.x;
    float x = ray.origin.x + t * direction.x;
    float y = ray.origin.y + t * direction.y;
    float z = ray.origin.z + t * direction.z;

    if (y > min_.y && y < max_.y && z > min_.z && z < max_.z){
      float distance = sqrt(pow(ray.origin.x - x, 2)+ pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
      HitPoint new_hit{true, distance, name_, material_, glm::vec3(x, y, z), direction};
      temp_hitpoint = new_hit;
      if (hitpoint.cdist >= 0 && temp_hitpoint.cdist >= 0 && temp_hitpoint.cdist < hitpoint.cdist){
        hitpoint = temp_hitpoint;
      }
    }
  }
  /*float t_max_x = (max_.x - ray.origin.x) / (glm::normalize(ray.direction)).x;
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
  if (direction.y != 0){
  float t = (-ray.origin.x + min_.y) / direction.y;
  float x = ray.origin.x + t * direction.x;
  float y = ray.origin.y + t * direction.y;
  float z = ray.origin.z + t * direction.z;

  if (x > min_.x && x < max_.x && z > min_.z && z < max_.z){
    float distance = sqrt(pow(ray.origin.x - x, 2)+ pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
    HitPoint new_hit{true, distance, name_, material_, glm::vec3(x, y, z), direction};
    temp_hitpoint = new_hit;
    if (hitpoint.cdist >= 0 && temp_hitpoint.cdist >= 0 && temp_hitpoint.cdist < hitpoint.cdist){
      hitpoint = temp_hitpoint;
    }     
  }
}
  /*float t_min_y = (min_.y - ray.origin.y) / (glm::normalize(ray.direction)).y;
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
  if (direction.y != 0){
  float t = (-ray.origin.x + max_.y) / direction.y;
  float x = ray.origin.x + t * direction.x;
  float y = ray.origin.y + t * direction.y;
  float z = ray.origin.z + t * direction.z;

  if (x > min_.x && x < max_.x && z > min_.z && z < max_.z){
    float distance = sqrt(pow(ray.origin.x - x, 2)+ pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
    HitPoint new_hit{true, distance, name_, material_, glm::vec3(x, y, z), direction};
    temp_hitpoint = new_hit;
    if (hitpoint.cdist >= 0 && temp_hitpoint.cdist >= 0 && temp_hitpoint.cdist < hitpoint.cdist){
      hitpoint = temp_hitpoint;
    }
  }
}
  /*float t_max_y = (max_.y - ray.origin.y) / (glm::normalize(ray.direction)).y;
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
  if (direction.z != 0){
  float t = (-ray.origin.x + max_.z) / direction.z;
  float x = ray.origin.x + t * direction.x;
  float y = ray.origin.y + t * direction.y;
  float z = ray.origin.z + t * direction.z;

  if (x > min_.x && x < max_.x && y > min_.y && y < max_.y){
    float distance = sqrt(pow(ray.origin.x - x, 2)+ pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
    HitPoint new_hit{true, distance, name_, material_, glm::vec3(x, y, z), direction};
    temp_hitpoint = new_hit;
    if (hitpoint.cdist >= 0 && temp_hitpoint.cdist >= 0 && temp_hitpoint.cdist < hitpoint.cdist){
      hitpoint = temp_hitpoint;
    }
  }
}
  /*float t_min_z = (min_.z - ray.origin.z) / (glm::normalize(ray.direction)).z;
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
if (direction.z != 0){
  float t = (-ray.origin.x + min_.z) / direction.z;
  float x = ray.origin.x + t * direction.x;
  float y = ray.origin.y + t * direction.y;
  float z = ray.origin.z + t * direction.z;

  if (x > min_.x && x < max_.x && y > min_.y && y < max_.y){
    float distance = sqrt(pow(ray.origin.x - x, 2)+ pow(ray.origin.y - y, 2) + pow(ray.origin.z - z, 2));
    HitPoint new_hit{true, distance, name_, material_, glm::vec3(x, y, z), direction};
    temp_hitpoint = new_hit;
    if (hitpoint.cdist >= 0 && temp_hitpoint.cdist >= 0 && temp_hitpoint.cdist < hitpoint.cdist){
      hitpoint = temp_hitpoint;
    }
  }
}
return hitpoint;

/*float t_max_z = (max_.z - ray.origin.z) / (glm::normalize(ray.direction)).z;
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
  return hitpoint; */

  
}

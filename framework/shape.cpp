#include "shape.hpp"


Shape::Shape():
  name_ {"default"},
  material_ {std::shared_ptr<Material> (new Material{})},
  world_transformation_ { 1.0f, 0.0f, 0.0f, 0.0f, 
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f, 
                          0.0f, 0.0f, 0.0f, 1.0f },
  world_transformation_inv_ {glm::inverse(world_transformation_)} {
  //std::cout << "Cnst/Shape " << name_ << "\n";
}

Shape::Shape(std::shared_ptr<Material> material,std::string const& name):
  material_ {material},
  name_ {name},
  world_transformation_ { 1.0f, 0.0f, 0.0f, 0.0f, 
                          0.0f, 1.0f, 0.0f, 0.0f,
                          0.0f, 0.0f, 1.0f, 0.0f, 
                          0.0f, 0.0f, 0.0f, 1.0f },
  world_transformation_inv_ {glm::inverse(world_transformation_)} {}

void Shape::transformation(glm::vec3 const& scale, 
                           glm::vec3 const& translation, float angle, 
                           glm::vec3 const& axis)
{
  //scaling
  
  glm::mat4 scaled_mat = glm::scale(world_transformation_, scale);

  //translation

  glm::mat4 translated_mat = 
            glm::translate(world_transformation_, translation);

  if (angle == 0.0f){
    world_transformation_ = world_transformation_ * translated_mat
                            * scaled_mat;
  }

  //rotation
  else{

    glm::mat4 rotated_mat = glm::rotate(world_transformation_, 
                                        glm::radians(angle), axis);
    
    world_transformation_ = world_transformation_ * translated_mat
                            * rotated_mat * scaled_mat;
  }

  world_transformation_inv_ = glm::inverse(world_transformation_);

}

void Shape::transform_rotation(float angle, glm::vec3 const& v) {
  if (angle != 0.0f) {
    world_transformation_ = glm::rotate(world_transformation_, 
                                        glm::radians(angle), v);
    world_transformation_inv_ = glm::inverse(world_transformation_);
  }
}

void Shape::transform_scale(glm::vec3 const& v) {
  world_transformation_ = glm::scale(world_transformation_, v);
  world_transformation_inv_ = glm::inverse(world_transformation_);
}

void Shape::transform_translation(glm::vec3 const& v) {
  world_transformation_ = glm::translate(world_transformation_, v);
  world_transformation_inv_ = glm::inverse(world_transformation_);
}


Ray transform_ray(Ray const& ray, glm::mat4 const& mat) 
{
  glm::vec4 p{ray.origin, 1.0f};
  glm::vec4 v{ray.direction, 0.0f};
  p = mat*p;
  v = mat*v;
  return {glm::vec3{p.x, p.y, p.z}, glm::vec3{v.x, v.y, v.z}};
}

void rev_trans(HitPoint & hitpoint, glm::mat4 const& world,
               glm::mat4 const& inv_world)
{
  hitpoint.hit = glm::vec3{world * glm::vec4{hitpoint.hit, 1.0f}};
  hitpoint.normal = glm::normalize(glm::vec3{inv_world * 
                    glm::vec4{hitpoint.normal, 0.0f}});
  hitpoint.direction = glm::normalize(glm::vec3{inv_world * 
                    glm::vec4{hitpoint.direction, 0.0f}});
 
}

Shape::~Shape() 
{
  //std::cout << "Dstr/Shape " << name_ << "\n";
}

std::ostream& Shape::print(std::ostream & os) const 
{
  return os 
  << "Shape "    << name_           << "\n"
  << "Material " << material_->name << "\n";
}

std::ostream& operator<<(std::ostream& os, Shape const& s) 
{
  return s.print(os);
}
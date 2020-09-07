#include "shape.hpp"


Shape::Shape():
  name_{"default name"},
  material_{},
  world_transformation_{1.0f, 0.0f, 0.0f, 0.0f, 
                        0.0f, 1.0f, 0.0f, 0.0f,
                        0.0f, 0.0f, 1.0f, 0.0f, 
                        0.0f, 0.0f, 0.0f, 1.0f},
  world_transformation_inv_ {glm::inverse(world_transformation_)} {
  //std::cout << "Cnst/Shape " << name_ << "\n";
}

Shape::Shape(std::shared_ptr<Material> material,std::string const& name):
material_{material},
name_{name},
world_transformation_{1.0f, 0.0f, 0.0f, 0.0f, 
                      0.0f, 1.0f, 0.0f, 0.0f,
                      0.0f, 0.0f, 1.0f, 0.0f, 
                      0.0f, 0.0f, 0.0f, 1.0f},
  world_transformation_inv_ {glm::inverse(world_transformation_)}{

}

void Shape::transformation(glm::vec3 const& scale, glm::vec3 const& translation, float angle, glm::vec3 const& axis){
  //scalation
  glm::mat4 scaled_mat = { scale.x, 0.0f, 0.0f, 0.0f,
                           0.0f, scale.y, 0.0f, 0.0f, 
                           0.0f, 0.0f, scale.z, 0.0f,
                           0.0f, 0.0f, 0.0f, 1.0f };


  //translation
  glm::mat4 translated_mat = { 1.0f, 0.0f, 0.0f, translation.x,
                               0.0f, 1.0f, 0.0f, translation.y,
                               0.0f, 0.0f, 1.0f, translation.z,
                               0.0f, 0.0f, 0.0f, 1.0f };

  if (angle == 0.0f){
    world_transformation_ = world_transformation_ * translated_mat * scaled_mat;
  }

  //rotation
  else{

    //rotation x-axis
    // if (axis.x == 1.0f){
    //   glm::mat4 rotated_mat_x = { 1.0f, 0.0f, 0.0f, 0.0f,
    //                               0.0f, std::cos(-angle.x), -std::sin(-angle.x), 0.0f,
    //                               0.0f, std::sin(-angle.x), std::cos(-angle.x), 0.0f,
    //                               0.0f, 0.0f, 0.0f, 1.0f };
    // }
    // //rotation y-axis
    // if (axis.y == 1.0f){
    //   glm::mat4 rotated_mat_y = { std::cos(-angle.y), 0.0f, std::sin(-angle.y), 0.0f,
    //                               0.0f, 1.0f, 0.0f, 0.0f,
    //                               -std::sin(-angle.y), 0.0f, std::cos(-angle.y), 0.0f,
    //                               0.0f, 0.0f, 0.0f, 1.0f };

    // }
    // //rotation z-axis
    // if (axis.z == 1.0f){
    //   glm::mat4 rotated_mat_z = { std::cos(-angle.z), -std::sin(-angle.z), 0.0f, 0.0f,
    //                               std::sin(-angle.z), std::cos(-angle.z), 0.0f, 0.0f,
    //                               0.0f, 0.0f, 1.0f, 0.0f,
    //                               0.0f, 0.0f, 0.0f, 1.0f };
    // }

    glm::mat4 rotated_mat = glm::rotate(world_transformation_, glm::radians(angle), axis);
    
    world_transformation_ = world_transformation_ * translated_mat * rotated_mat * scaled_mat;
  }

  world_transformation_inv_ = glm::inverse(world_transformation_);

}

Shape::~Shape() {
  //std::cout << "Dstr/Shape " << name_ << "\n";
}

std::ostream& Shape::print(std::ostream & os) const {
   return os << "Shape " << name_ << "\nMaterial name " << material_->name << "\n\n";
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
  return s.print(os);
}
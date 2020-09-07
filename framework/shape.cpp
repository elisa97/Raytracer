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



Shape::~Shape() {
  //std::cout << "Dstr/Shape " << name_ << "\n";
}

std::ostream& Shape::print(std::ostream & os) const {
   return os << "Shape " << name_ << "\nMaterial name " << material_->name << "\n\n";
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
  return s.print(os);
}
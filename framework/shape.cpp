#include "shape.hpp"

Shape::Shape() {
  std::cout << "Cnst/Shape " << name_ << "\n";
}

Shape::~Shape() {
  std::cout << "Dstr/Shape " << name_ << "\n";
}

std::ostream& Shape::print(std::ostream & os) const {
   return os << "Shape " << name_ << "\nRGB " << color_.r 
          << "|" << color_.g << "|" << color_.b << "\n\n";
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
  return s.print(os);
}
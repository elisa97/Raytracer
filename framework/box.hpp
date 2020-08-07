#ifndef BOX_HPP
#define BOX_HPP

#include <glm/vec3.hpp>
#include "shape.hpp"

class Box : public Shape {
  public:
    Box();
    Box(glm::vec3 const& lhs, glm::vec3 const& rhs);
    Box(glm::vec3 const& lhs, glm::vec3 const& rhs, 
        std::string const& n, Color const& c);
        
    float area() const override;
    float volume() const override;
    std::ostream& print(std::ostream & os) const override;
  private:
    glm::vec3 topr_, botl_;
};

#endif
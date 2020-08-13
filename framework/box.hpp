#ifndef BOX_HPP
#define BOX_HPP

// header, external
#include <glm/vec3.hpp>

// header, system
#include "cmath"

// header, project
#include "shape.hpp"

class Box : public Shape {
  public:
    Box();
    Box(glm::vec3 const& lhs, glm::vec3 const& rhs);
    Box(glm::vec3 const& lhs, glm::vec3 const& rhs, 
        std::string const& name, std::shared_ptr<Material> material);
        
    float area() const override;
    float volume() const override;
    std::ostream& print(std::ostream & os) const override;
    HitPoint intersect(Ray const& ray) const override;
  private:
    glm::vec3 min_, max_;
};



#endif